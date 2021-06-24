#pragma once

#include <fstream>

namespace kr {
namespace utility {

bool save_file(const char *name, const char *buf, size_t len, bool binary);

inline bool save_file(const char *name, const std::string &buf, bool binary)
{
    return save_file(name, buf.c_str(), buf.size(), binary);
}

} // namespace utility
} // namespace kr