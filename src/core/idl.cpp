#include "idl.h"
#include <stdexcept>

#include "IDLLexer.h"
#include "IDLParser.h"
#include "CellLexer.h"
#include "CellParser.h"
#include "ast_builder.h"


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
bool Parser::Parse(const std::string& source) {
  using namespace antlr4;
  ANTLRInputStream input(source);
  IDLLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  IDLParser parser(&tokens);

  IDLAstBuilder ast_builder;
  auto tree = parser.program();
  try {
    type_ = ast_builder.visitProgram(tree).as<Type>();
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return false;
  }
  std::cout << tree->toStringTree(&parser, true) << std::endl;
  return true;
}

bool Parser::ParseCell(const std::string& source)
{ 
    using namespace antlr4;
    ANTLRInputStream input(source);
    CellLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CellParser parser(&tokens);
    
    msgpack::sbuffer buffer;
    Packer<msgpack::packer<msgpack::sbuffer>> packer{buffer};
    CellAstBuilder ast_builder{packer};

    auto tree = parser.program();
    ast_builder.visitProgram(tree);

    std::string json_like;
    json_like_visitor v(json_like);
    std::size_t offset = 0;
    bool ret = msgpack::parse(buffer.data(), buffer.size(), offset, v);
    std::cout << json_like << std::endl;
    return true;
}

Type Parser::Message() const { return type_; }
} // namespace core
} // namespace kr