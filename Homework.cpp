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
    if(argc < 2)
    {
        std::cerr << "Plase specify filename to parse.\n";
        return -1;
    }
    else if(argc > 2)
    {
        std::cout << "Additional parameters apart from first (FileName) will be ignored.\n";
    }

    // ==== read file ====
    float timer = helpers::dclock();
    std::string text = helpers::getFileContents(argv[1]);
    timer = helpers::dclock() - timer;

    std::cout << std::format("File reading took: {}\n", helpers::dclock_to_string(timer));

#if DLOG
    std::cout << std::format("File contents are: \n{}\n", text);
    // ===================

    std::cout << "=====================\n";
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

    std::cout << std::format("Text processing took: {}\n", helpers::dclock_to_string(timer));

#if DLOG
    std::cout << std::format("Parsed contents are: \n{}\n", text);
#endif

    return 0;
}
