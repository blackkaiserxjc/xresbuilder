#pragma once

#include <string>

namespace kr {
namespace core {
namespace generator {

std::string underscores_to_camelcase(const std::string &input,
    bool lower_first = true);

std::string underscores_to_pascalcase(const std::string &input);

} // namespace generator
} // namespace core
} // namespace kr