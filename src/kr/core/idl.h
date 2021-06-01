#pragma once

#include <memory>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <msgpack.hpp>

#include <kr/core/type.h>
#include <kr/core/pack.h>
#include <kr/core/object_pack.h>

struct json_like_visitor : msgpack::null_visitor {
    json_like_visitor(std::string& s):m_s(s) {}

    bool visit_nil() {
        m_s += "null";
        return true;
    }
    bool visit_boolean(bool v) {
        if (v) m_s += "true";
        else m_s += "false";
        return true;
    }
    bool visit_positive_integer(uint64_t v) {
        std::stringstream ss;
        ss << v;
        m_s += ss.str();
        return true;
    }
    bool visit_negative_integer(int64_t v) {
        std::stringstream ss;
        ss << v;
        m_s += ss.str();
        return true;
    }
    
    bool visit_float32(float v) 
    {
        std::stringstream ss;
        ss << v;
        m_s += ss.str();
        return true;
    }

    bool visit_float64(double v)
    {
        std::stringstream ss;
        ss << v;
        m_s += ss.str();
        return true;
    }

    bool visit_str(const char* v, uint32_t size) {
        // I omit escape process.
        m_s += '"' + std::string(v, size) + '"';
        return true;
    }
    bool start_array(uint32_t /*num_elements*/) {
        m_s += "[";
        return true;
    }
    bool end_array_item() {
        m_s += ",";
        return true;
    }
    bool end_array() {
        m_s.erase(m_s.size() - 1, 1); // remove the last ','
        m_s += "]";
        return true;
    }
    bool start_map(uint32_t /*num_kv_pairs*/) {
        m_s += "{";
        return true;
    }
    bool end_map_key() {
        m_s += ":";
        return true;
    }
    bool end_map_value() {
        m_s += ",";
        return true;
    }
    bool end_map() {
        m_s.erase(m_s.size() - 1, 1); // remove the last ','
        m_s += "}";
        return true;
    }
    void parse_error(size_t /*parsed_offset*/, size_t /*error_offset*/) {
    }
    void insufficient_bytes(size_t /*parsed_offset*/, size_t /*error_offset*/) {
    }
    std::string& m_s;
};


namespace kr {
namespace core {

class Model;

bool parse_data(const std::string& source, Packer<msgpack::packer<msgpack::sbuffer>>& packer);

bool parse_field(const std::string& source, Type& type);

bool generate_json(Model& model, const std::string& path, const std::string& file_name);

bool generate_lua(Model& model, const std::string& path, const std::string& file_name);

/** 解析器 */
class Parser {
public:
  Parser() = default;
  ~Parser() = default;

  Parser(const Parser &) = delete;
  Parser &operator=(const Parser &) = delete;

  bool Parse(const std::string &field, const std::string& cell);
  bool ParseField(const std::string& source);
  msgpack::object ParseCell(const std::string &source);
  Type Message() const;

protected:
  Type type_;
};
} // namespace core
} // namespace kr