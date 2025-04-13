
#include "Helpers_3.h"

bool text_processing::is_letter(char c)
{
    return c >= 32u && c <= 126u;
}

bool text_processing::is_white_sign(char c)
{
    return c == TAB || c == ENTER || c == SPACE;
}

bool text_processing::is_supper(char c)
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
    [[maybe_unused]] auto it = std::remove_if(input.begin(), input.end(), [](const char& c) 
    { 
        return !is_letter(c) && !is_white_sign(c);
    });

    for (auto it = input.end(); it != input.begin(); --it)
    {
        if(is_white_sign(*it))
        {
            // remove subsequent white signs
            if(it - 1 != input.begin())
            {
                if(is_white_sign(*(it-1)))
                {
                    input.erase(it);
                    continue;
                }
            }
            
            *it = SPACE;
            continue;
        }
    }

    std::transform(input.begin(), input.end(), input.begin(), [](char c) 
    {
        if(is_supper(c))
        {
            c = ascii_to_lower(c);
        }
        else if(is_interpunction_char(c))
        {
            c = ',';
        }

        return c;
    });

    remove_sequential_duplicates(input);
}

void text_processing::remove_sequential_duplicates(std::string &input)
{
    std::string prev_word;
    std::string curr_word;

    auto it = input.end() - 1;
    for (; it != input.begin() - 1; --it)
    {
        if(*it == SPACE || *it == COMMA)
        {
            if(prev_word == curr_word)
            {
                input.erase(it, it + curr_word.size());
            }

            prev_word = curr_word;
            curr_word.clear();
        }

        curr_word.push_back(*it);
    }

    if(prev_word == curr_word)
    { 
        it += 1;
        input.erase(it, it + curr_word.size());
    }
}
