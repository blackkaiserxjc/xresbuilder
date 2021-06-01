#include "code_generator.h"

namespace kr {
namespace core {

void CodeWriter::operator+=(std::string text)
{
    while (true)
    {
        auto begin = text.find("{{");
        if (begin == std::string::npos)
        {
          break;
        }
        auto end = text.find("}}");
        if (end == std::string::npos || end < begin)
        {
          break;
        }
        stream_.write(text.c_str(), begin);

        const std::string key = text.substr(begin + 2, end - begin - 2);
        auto iter = value_map_.find(key);
        if (iter != value_map_.end())
        {
          const std::string &value = iter->second;
          stream_ << value;
        }
        else
        {
          stream_ << key;
        }
        text = text.substr(end + 2);
    }
    
    if (!text.empty() && text.back() == '\\')
    {
        text.pop_back();
        stream_ << text;
    }
    else
    {
        stream_ << text;
    }
}

} // namespace core
} // namespace kr