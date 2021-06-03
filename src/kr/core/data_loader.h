#pragma once
#include "antlr4-runtime.h"

#include <string>

#include <boost/core/noncopyable.hpp>

namespace kr {
namespace core {

class DataTable;
class DataLoader : boost::noncopyable {
public:
  static bool execute(const std::string &path, DataTable &table);

private:
  static bool load_from_csv(const std::string &path, DataTable &table);
  static bool load_from_xlsx(const std::string &path, DataTable &table);
};

} // namespace core
} // namespace kr