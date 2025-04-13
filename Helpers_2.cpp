#include "Helpers_2.h"

bool text_processing::is_letter(char c)
{
    return c >= 32u && c <= 126u;
}

bool text_processing::is_white_sign(char c)
{
    return c == TAB || c == ENTER || c == SPACE;
}

bool text_processing::is_upper(char c)
{
    return c <= 'Z' && c >= 'A';
}

char text_processing::ascii_to_lower(char c)
{
    static constexpr uint8_t char_diff = 'Z' - 'z';

    if (c <= 'Z' && c >= 'A')
    {
        return c - char_diff;
    }

    return c;

}

bool text_processing::is_interpunction_char(char c)
{
    return c == '.'
        || c == '-'
        || c == ','
        || c == ':'
        || c == ';'
        || c == '?'
        || c == '!'
        || c == '"'
        || c == '('
        || c == ')'
        || c == '['
        || c == ']'
        || c == '{'
        || c == '}'
        || c == '\''
        ;
}

void text_processing::process(std::string &input)
{
    std::string curr_word, prev_word;

    for (int index = input.size() - 1; index >= 0; --index)
    {
        char& c = input[index];
        if(!is_letter(c) && !is_white_sign(c))
        {
            input.erase(index, 1);
            continue;
        }

        if(is_upper(c))
        {
            c = ascii_to_lower(c);
            curr_word += c;
        }
        else if(is_interpunction_char(c))
        {
            c = ',';
            curr_word += c;
        }
        else if(is_white_sign(c) == false)
        {
            curr_word += c;
        }
        else
        {
            if(curr_word.empty() == false)
            {
                if(prev_word == curr_word)
                {
                    input.erase(index + 1, curr_word.size());
                }
    
                prev_word = curr_word;
                curr_word.clear();
            }

            while(index > 0 && is_white_sign(input[index - 1]))
            {
                input.erase(index, 1);
                --index;
            }

            c = SPACE;
        }
    }

    if(is_white_sign(input[0]) && is_white_sign(input[1]))
    {
        input.erase(0, 1);
    }
    
    if(curr_word == prev_word)
    {
        input.erase(0, curr_word.size());
    }
}
