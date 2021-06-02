#pragma once

#include <string>

namespace kr {
namespace core {

class Model;

extern bool generate_json(Model& model, const std::string& path, const std::string& file_name);

extern bool generate_lua(Model& model, const std::string& path, const std::string& file_name);

} // namespace core
} // namespace kr