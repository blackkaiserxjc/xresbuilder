#pragma once

#include <string>

#include <boost/core/noncopyable.hpp>

namespace kr {
namespace core {

class DataTable;
class DataLoader : boost::noncopyable
{
public:
    static bool load_from_csv(const std::string& path, DataTable& table);
    static bool load_from_excel(const std::string& path, DataTable& table);
};

}
} // namespace kr