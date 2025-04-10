#include <string>

namespace helpers
{
  std::string getFileContents(const char* file_name);

  double dclock();

  std::string dclock_to_string(double in_dclock);
}

namespace text_processing
{
    static constexpr char TAB = '\t';
    static constexpr char ENTER = '\n';
    static constexpr char SPACE = ' ';
    static constexpr char COMMA = ',';

    bool is_letter(char c);
    bool is_white_sign(char c);
    bool is_supper(char c);
    char ascii_to_lower(char c);
    bool is_interpunction_char(char c);
    bool words_equal(std::vector<char>* w1, std::vector<char>* w2);

    std::string process(std::string& input);

    std::string remove_not_letters(std::string input);
    std::string squash_white_signs(std::string input);
    std::string to_lower(std::string input);
    std::string convert_interp_to_commas(std::string input);
    std::string remove_sequential_duplicates(std::string input);
}