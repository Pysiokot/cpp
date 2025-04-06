#include <string>

namespace helpers
{
  std::string getFileContents(const char* file_name);

  double dclock();

  std::string dclock_to_string(double in_dclock);
}

namespace text_processing
{
    std::string process(std::string&& input);
}