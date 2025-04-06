#include <format>
#include <string.h>
#include <iostream>

#include "Helpers.h"
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
    std::cout << std::format("File contents are: {}\n", text);
    // ===================

    std::cout << "=====================\n";
#endif

    std::string result = text_processing::process(text);

#if DLOG
    std::cout << std::format("Parsed contents are: \n{}\n", text);
#endif

    return 0;
}
