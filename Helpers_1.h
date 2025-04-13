#include <string>

namespace text_processing
{
    static constexpr char TAB = '\t';
    static constexpr char ENTER = '\n';
    static constexpr char SPACE = ' ';
    static constexpr char COMMA = ',';

    bool is_letter(char c);
    bool is_white_sign(char c);
    bool is_upper(char c);
    char ascii_to_lower(char c);
    bool is_interpunction_char(char c);

    std::string process(std::string& input);
}