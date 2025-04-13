#include "vector"

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

std::string text_processing::transform_chars(std::string::iterator start_it, std::string::iterator end_it)
{
    std::string result;
    result.reserve(std::distance(start_it, end_it));

    for (std::string::iterator it = start_it; it != end_it; ++it)
    {
        if (is_letter(*it) == false)
        {
            continue;
        }
        else if (is_upper(*it))
        {
            result += tolower(*it);
        }
        else if (is_interpunction_char(*it))
        {
            result += ',';
        }
        else if (is_white_sign(*it) == false)
        {
            result += *it;
        }
    }

    return result;
}

std::string text_processing::process(std::string &input)
{
    static constexpr int BLOCK_SIZE = 10000;
    size_t blockCount = (input.size() + BLOCK_SIZE - 1) / BLOCK_SIZE;
    std::vector<std::string> partialResults(blockCount);

    #pragma omp parallel for
    for (size_t i = 0; i < blockCount; ++i)
    {
        auto start_it = input.begin() + i * BLOCK_SIZE;
        auto end_it = (i + 1) * BLOCK_SIZE < input.size() ? start_it + BLOCK_SIZE : input.end();
        partialResults[i] = transform_chars(start_it, end_it);
    }

    size_t input_size = input.size();
    input.clear();
    input.reserve(input_size);

    for (auto part : partialResults)
    {
        input += part;
    }

    std::string result, currentWord, previousWord;
    for (auto it = input.begin(); it != input.end(); ++it)
    {
        if (!isspace(*it))
        {
            currentWord += *it;
        }
        else if ((it + 1) == input.end() || !isspace(*(it + 1)))
        {
            if (previousWord != currentWord)
            {
                result.append(currentWord);
                result += ' ';
            }

            previousWord = currentWord;
            currentWord.clear();
        }
    }

    if (currentWord != previousWord)
    {
        result.append(currentWord);
    }

    return result;
}
