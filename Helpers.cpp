#include <sys/time.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <format>
#include <vector>

#include "Helpers.h"

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

bool text_processing::is_supper(char c)
{
    return c <= 'Z' && c >= 'A';
}

char text_processing::ascii_to_lower(char c)
{
    static constexpr uint8_t char_diff = 'Z' - 'z';

    return c - char_diff;
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

std::string text_processing::process(std::string& input)
{
    std::string result = "";
    std::string curr_word, prev_word = "";
    for (size_t index = 0; index < input.size(); ++index)
    {
        if(!is_letter(input[index]) && !is_white_sign(input[index]))
        {
            continue;
        }
        if(is_supper(input[index]))
        {
            curr_word += ascii_to_lower(input[index]);
        }
        else if(is_interpunction_char(input[index]) == false && is_white_sign(input[index]) == false)
        {
            curr_word += input[index];
        }
        else if(is_interpunction_char(input[index]))
        {
            curr_word += ',';
        }
        else if(is_white_sign(input[index]))
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
    
    return result;
}

std::string text_processing::remove_not_letters(std::string input)
{
    for (int index = input.size() - 1; index >= 0; --index)
    {
        if(is_letter(input[index]) || is_white_sign(input[index]))
        {
            continue;
        }

        input.erase(index, 1);
    }

    return input;
}

std::string text_processing::squash_white_signs(std::string input)
{
    for (int index = input.size() - 1; index >= 0; --index)
    {
        if(is_white_sign(input[index]) == false)
        {
            continue;
        }

        if(index - 1 >= 0)
        {
            if(is_white_sign(input[index -1]))
            {
                input.erase(index, 1);
                continue;
            }
        }

        input[index] = SPACE;
    }

    return input;
}

std::string text_processing::to_lower(std::string input)
{
    for (int index = 0; index < input.size(); ++index)
    {
        input[index] = ascii_to_lower(input[index]);
    }

    return input;
}

std::string text_processing::convert_interp_to_commas(std::string input)
{
    for (int index = input.size() - 1; index >= 0; --index)
    {
        if(is_interpunction_char(input[index]) == false)
        {
            continue;
        }

        // handle '...'
        if(input[index] == '.')
        {
            const int index_1 = index - 1;
            if(index_1 > 0 && input[index_1] == '.')
            {
                const int index_2 = index - 2;
                if(index_2 >= 0 && input[index_2] == '.')
                {
                    input.erase(index_1, 2);
                    index = index_2;
                }
            }
        }

        input[index] = ',';
    }

    return input;
}

std::string text_processing::remove_sequential_duplicates(std::string input)
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

    return input;
}
