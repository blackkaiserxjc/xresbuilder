#include <kr/utility/utility.h>

namespace kr {
namespace utility {

bool save_file(const char *name, const char *buf, size_t len, bool binary)
{
    std::ofstream ofs(name, binary ? std::ofstream::binary : std::ofstream::out);
    if (!ofs.is_open())
    {
        return false;
    }
    ofs.write(buf, len);
    return !ofs.bad();
}

} // namespace utility
} // namespace kr