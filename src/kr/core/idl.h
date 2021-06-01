#pragma once

#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <msgpack.hpp>

#include <kr/core/type.h>
#include <kr/core/pack.h>
#include <kr/core/object_pack.h>

namespace kr {
namespace core {

class Model;

bool parse_data(const std::string& source, Packer<msgpack::packer<msgpack::sbuffer>>& packer);

bool parse_field(const std::string& source, Type& type);

bool generate_json(Model& model, const std::string& path, const std::string& file_name);

bool generate_lua(Model& model, const std::string& path, const std::string& file_name);

} // namespace core
} // namespace kr