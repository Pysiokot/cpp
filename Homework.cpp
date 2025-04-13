#include <format>
#include <string.h>
#include <iostream>

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
#endif

#include "Homework.h"

int main(int argc, const char* argv[])
{
    // ==== read file ====
    float timer = helpers::dclock();
    const std::string file_contents = helpers::getFileContents("test.txt");
    timer = helpers::dclock() - timer;
    std::string text = file_contents;

    std::cout << std::format("File reading took: {}\n", helpers::dclock_to_string(timer));

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
    std::cout << std::format("Text processing took: {}\n", helpers::dclock_to_string(timer));
#endif
#if BENCH
    full_time += timer;
}
full_time /= reps;
std::cout << std::format("Avg text processing took: {}\n", helpers::dclock_to_string(full_time));
#endif

#if DLOG
    std::cout << std::format("Parsed contents are: \n{}\n", text);
#endif

    return 0;
}
