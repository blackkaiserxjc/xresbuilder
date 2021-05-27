#ifndef KR_APP_CORE_IDL_H_
#define KR_APP_CORE_IDL_H_

#include <memory>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "type.h"
#include "object_pack.h"

namespace kr {
namespace core {

template <typename Stream>
bool parse_cell(const std::string& source, Stream& output)
{
  using namespace antlr4;
  try {
    ANTLRInputStream input(source);
    CellLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CellParser parser(&tokens);
    
    Packer<msgpack::packer<Stream>> packer{output};
    CellAstBuilder ast_builder{packer};
    ast_builder.visitProgram(parser.program());
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return false;
  }
  return true;
}

inline bool parse_field(const std::string& source, Type& type)
{
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
      std::cerr << e.what() << std::endl;
      return false;
    }
    return true;
}

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

#endif /* KR_APP_CORE_IDL_H_ */