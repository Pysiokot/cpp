#include <sys/time.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <format>

#include "Helpers.h"

namespace helpers
{
    static double gtod_ref_time_sec = 0.0;
}

std::string helpers::getFileContents(const char *file_name)
{
    auto size = std::filesystem::file_size(file_name);
    std::string content(size, '\0');
    std::ifstream in(file_name);
    in.read(&content[0], size);

    return std::move(content);
    // std::ifstream input_stream(file_name);

    // if (!input_stream)
    // {
    // std::cerr << "Can't open input file!";
    // return "";
    // } 

    // std::string full_text;

    // std::string line;
    // while (getline(input_stream, line)) 
    // {
    //     // store each line in the vector
    //     full_text += line;
    // }

    // return std::move(full_text);
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

std::string text_processing::process(std::string &&input)
{
  return input;
}