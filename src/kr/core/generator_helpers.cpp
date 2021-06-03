#include <kr/core/generator_helpers.h>

#include <locale>

namespace kr {
namespace core {
namespace generator {

std::string underscores_to_camelcase(const std::string &input,
                                     bool lower_first) {
  bool capitalize_next = !lower_first;
  std::string result;
  result.reserve(input.size());

  for (char character : input) {
    if (character == '_') {
      capitalize_next = true;
    } else if (capitalize_next) {
      result.push_back(std::toupper(character, std::locale::classic()));
      capitalize_next = false;
    } else {
      result.push_back(character);
    }
  }

  if (lower_first && !result.empty()) {
    result[0] = std::tolower(result[0], std::locale::classic());
  }

  return result;
}

std::string underscores_to_pascalcase(const std::string &input) {
  bool next_upper = true;
  std::string result;
  result.reserve(input.size());

  for (char character : input) {
    if (character == '_') {
      next_upper = true;
    } else {
      if (next_upper) {
        result.push_back(std::toupper(character, std::locale::classic()));
      } else {
        result.push_back(std::tolower(character, std::locale::classic()));
      }
      next_upper = false;
    }
  }

  return result;
}

} // namespace generator
} // namespace core
} // namespace kr