
#include "Helpers_1.h"

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

    if (is_upper(c))
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

std::string text_processing::process(std::string &input)
{
    std::string result;
    result.reserve(input.size());

    std::string curr_word, prev_word;
    curr_word.reserve(16);
    prev_word.reserve(16);

    for (size_t index = 0; index < input.size(); ++index)
    {
        if(!is_letter(input[index]) && !is_white_sign(input[index]))
        {
            continue;
        }
        if(is_upper(input[index]))
        {
            curr_word += ascii_to_lower(input[index]);
        }
        else if(is_interpunction_char(input[index]))
        {
            curr_word += ',';
        }
        else if (is_white_sign(input[index]) == false)
        {
            curr_word += input[index];
        }
        else
        {
            while(index + 1 < input.size() && is_white_sign(input[index + 1]))
            {
                ++index;
            }

            if(curr_word != prev_word)
            {
                result.append(curr_word);
                result += SPACE;
            }

            prev_word = curr_word;
            curr_word.clear();
        }
    }

    result.append(curr_word);
    
    return std::move(result);
}
