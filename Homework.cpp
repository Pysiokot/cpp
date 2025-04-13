#include <format>
#include <string.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <time.h>
#include <sys/time.h>

#if ZERO
#include "Helpers.h"
#elif ONE
#include "Helpers_1.h"
#elif TWO
#include "Helpers_2.h"
#elif THREE
#include "Helpers_3.h"
#elif FOUR
#include "Helpers_4.h"
#elif FIVE
#include "Helpers_5.h"
#endif

#include "Homework.h"

std::string helpers::getFileContents(const char *file_name)
{
    std::ifstream ifs(file_name);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                        (std::istreambuf_iterator<char>()    ) );
    // auto size = std::filesystem::file_size(file_name);
    // std::string content (size, '\0');
    // std::ifstream in(file_name);
    // in.read(&content[0], size);

    return std::move(content);
}

namespace helpers
{
    static double gtod_ref_time_sec = 0.0;
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

int main(int argc, const char* argv[])
{
    // ==== read file ====
    float timer = helpers::dclock();
    const std::string file_contents = helpers::getFileContents("test.txt");
    timer = helpers::dclock() - timer;
    std::string text = file_contents;

#if BENCH
static constexpr int reps = 2000;
float full_time = 0.f;
for (int i = 0; i < reps; ++i)
{
    text = file_contents;
#endif
    timer = helpers::dclock();
    #if ZERO || ONE
        text = text_processing::process(text);
    #elif FOUR
    char* res = text_processing::process(text);
    #else
        text_processing::process(text);
    #endif
    timer = helpers::dclock() - timer;

#if !BENCH
    std::cout << text;
    // std::cout << "Text processing took: " << timer << "\n";
#endif
#if BENCH
    std::cout << "Text processing took: " << timer << "\n";

    full_time += timer;
}
full_time /= reps;
std::cout << "Avg text processing took: " << full_time << "\n";
#endif

    return 0;
}
