#include <kr/core/code_generator.h>

namespace kr {
namespace core {

void CodeWriter::indent()
{
    cur_ident_lvl_++;
}

void CodeWriter::outdent()
{
    if (cur_ident_lvl_)
        cur_ident_lvl_--;
}

void CodeWriter::append_ident(std::stringstream &stream)
{
    int lvl = cur_ident_lvl_;
    while (lvl--)
    {
        stream.write(pad_.c_str(), static_cast<std::streamsize>(pad_.size()));
    }
}

void CodeWriter::operator+=(std::string text)
{
    if (!ignore_ident_ && !text.empty()) append_ident(stream_);
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
        ignore_ident_ = true;
        stream_ << text;
    }
    else
    {
        ignore_ident_ = false;
        stream_ << text << std::endl;
    }
}

const char *CodeGenerator::generated_warning()
{
    return "automatically generated by the xresbuilder, do not modify";
}

} // namespace core
} // namespace kr