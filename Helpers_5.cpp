#include "Helpers_5.h"

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

char* text_processing::process(std::string &input)
{
    char* result = (char *)calloc(input.size(), sizeof(char));
    char *curr_word = (char *)calloc(input.size(), sizeof(char));
    char *prev_word = (char *)calloc(input.size(), sizeof(char));
    size_t curr_word_size = 0, prev_word_size = 0;

    for (size_t index = 0; index < input.size(); ++index)
    {
        char& c = input[index];
        if(!is_letter(c) || !is_white_sign(c))
        {
            continue;
        }

        if (is_upper(c))
        {
            curr_word[curr_word_size++] = tolower(c);
        }
        else if (is_interpunction_char(c))
        {
            curr_word[curr_word_size++] = ',';
        }
        else if (!is_white_sign(c))
        {
            curr_word[curr_word_size++] = c;
        }
        else
        {
            while(index + 1 < input.size() && is_white_sign(input[index + 1]))
            {
                ++index;
            }
            
            if (curr_word_size != prev_word_size ||
                strncmp(prev_word, curr_word, curr_word_size))
            {
                memcpy(result, curr_word, curr_word_size);
                result += curr_word_size;
                *result = SPACE;
                ++result;
            }

            memcpy(prev_word, curr_word, curr_word_size);
            prev_word[curr_word_size] = '\0';
            prev_word_size = curr_word_size;
            curr_word_size = 0u;
        }
    }

    memcpy(result, curr_word, curr_word_size);
    result += curr_word_size;
    *result = '\0';

    free(curr_word);
    free(prev_word);

    return result;
}
