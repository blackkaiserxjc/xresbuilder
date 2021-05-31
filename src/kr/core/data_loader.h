#pragma once

#include <string>

#include <boost/core/noncopyable.hpp>

namespace kr {
namespace core {

class DataTable;
class DataLoader : boost::noncopyable
{
public:
    static bool LoadFromCSV(const std::string& path, DataTable& table);
    static bool LoadFromExecl(const std::string& path, DataTable& table);
};

}
} // namespace kr