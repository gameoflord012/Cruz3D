#include <string>

namespace cruz
{
inline std::string GetDir(std::string filePath)
{
    size_t slash_index = filePath.rfind('/');

    if (std::string::npos != slash_index)
    {
        return filePath.substr(0, slash_index);
    }

    return ".";
}
} // namespace cruz