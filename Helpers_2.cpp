#include <sys/time.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <format>
#include <vector>

#include "Helpers_2.h"

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

bool text_processing::words_equal(std::vector<char> *w1, std::vector<char> *w2)
{
    if(w1->size() != w2->size())
    {
        return false;
    }

    for (int i = 0; i < w1->size(); ++i)
    {
        if(w1->at(i) != w2->at(i))
        {
            return false;
        }
    }

    return true;
}

void text_processing::process(std::string &input)
{
    for (int index = input.size() - 1; index >= 0; --index)
    {
        if(!is_letter(input[index]) && !is_white_sign(input[index]))
        {
            input.erase(index, 1);
            continue;
        }

        if(is_white_sign(input[index]))
        {
            if(index - 1 >= 0)
            {
                if(is_white_sign(input[index -1]))
                {
                    input.erase(index, 1);
                    continue;
                }
            }
            input[index] = SPACE;
            continue;
        }

        input[index] = ascii_to_lower(input[index]);

        if(is_interpunction_char(input[index]))
        {
            input[index] = ',';
        }
    }

    remove_sequential_duplicates(input);
}

void text_processing::remove_sequential_duplicates(std::string &input)
{
    std::vector<char> prev_word;
    std::vector<char> curr_word;

    for (int index = input.size() - 1; index >= 0; --index)
    {
        if(input[index] == SPACE || input[index] == COMMA)
        {
            if(words_equal(&prev_word, &curr_word) && prev_word.empty() == false)
            {
                input.erase(index + 1, curr_word.size());
            }

            prev_word = curr_word;
            curr_word.clear();
        }

        curr_word.insert(curr_word.begin(), input[index]);
    }

    if(words_equal(&prev_word, &curr_word))
    {
        input.erase(0, curr_word.size());
    }
}
