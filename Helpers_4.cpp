#include <sys/time.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <format>
#include <vector>

#include "Helpers_4.h"

namespace helpers
{
    static double gtod_ref_time_sec = 0.0;
}

std::string helpers::getFileContents(const char *file_name)
{
    auto size = std::filesystem::file_size(file_name);
    std::string content (size, '\0');
    std::ifstream in(file_name);
    in.read(&content[0], size);

    return std::move(content);
}

double helpers::dclock()
{
    double the_time, norm_sec;
    struct timeval tv;

    gettimeofday( &tv, NULL );

    if ( gtod_ref_time_sec == 0.0 )
    {
      gtod_ref_time_sec = ( double ) tv.tv_sec;
    }

    norm_sec = ( double ) tv.tv_sec - gtod_ref_time_sec;
    the_time = norm_sec + tv.tv_usec * 1.0e-6;
    
    return the_time;
}

std::string helpers::dclock_to_string(double in_dclock)
{
    if(in_dclock < 0.0)
    {
      return "";
    }

    if(in_dclock >= 0.1)
    {
      return std::format("{} s", in_dclock);
    }

    in_dclock *= 1000;

    return std::move(std::format("{} ms", in_dclock));
}

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
        if(!is_letter(input[index]) || !is_white_sign(input[index]))
        {
            continue;
        }

        if (is_upper(input[index]))
        {
            curr_word[curr_word_size++] = tolower(input[index]);
        }
        else if (is_interpunction_char(input[index]))
        {
            curr_word[curr_word_size++] = ',';
        }
        else if (!is_white_sign(input[index]))
        {
            curr_word[curr_word_size++] = input[index];
        }
        else if (index + 1 == input.size() || !is_white_sign(input[index + 1]))
        {
            if (curr_word_size != prev_word_size ||
                strncmp(prev_word, curr_word, curr_word_size))
            {
                memcpy(result, curr_word, curr_word_size);
                result += curr_word_size;
                *result = ' ';
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
