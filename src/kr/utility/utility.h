#pragma once

#include <fstream>

namespace kr {
namespace utility {

inline bool save_file(const char* name, const char *buf, size_t len, bool binary)
{
    std::ofstream ofs(name, binary ? std::ofstream::binary : std::ofstream::out);
    if (!ofs.is_open())
    {
        return false;
    }
    ofs.write(buf, len);
    return !ofs.bad();
}

inline bool save_file(const char* name, const std::string& buf, bool binary)
{
    return save_file(name, buf.c_str(), buf.size(), binary);
}

}
}