#include "idl.h"
#include <stdexcept>

#include "IDLLexer.h"
#include "IDLParser.h"
#include "CellLexer.h"
#include "CellParser.h"
#include "ast_builder.h"

namespace kr {
namespace core {
bool parse_data(const std::string& source, Packer<msgpack::packer<msgpack::sbuffer>>& packer)
{
  using namespace antlr4;
  ANTLRInputStream input(source);
  CellLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  CellParser parser(&tokens);
  try {
    CellAstBuilder ast_builder{packer};
    ast_builder.visitProgram(parser.program());
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return false;
  }
  return true;
}

bool parse_field(const std::string& source, Type& type)
{
    using namespace antlr4;
    ANTLRInputStream input(source);
    IDLLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    IDLParser parser(&tokens);

    IDLAstBuilder ast_builder;
    auto tree = parser.program();
    try {
      type = ast_builder.visitProgram(tree).as<Type>();
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
      return false;
    }
    return true;
}
}
}


namespace kr {
namespace core {

bool Parser::Parse(const std::string& field, const std::string& cell) {
    ParseField(field);
    auto object = ParseCell(cell);

    msgpack::sbuffer sbuffer;
    Packer<msgpack::packer<msgpack::sbuffer>> packer(sbuffer);
    UnPacker<msgpack::object> unpacker(object);
    pack(packer, type_, unpacker);

    std::string json_like;
    json_like_visitor v(json_like);
    std::size_t offset = 0;
    bool ret = msgpack::parse(sbuffer.data(), sbuffer.size(), offset, v);
    std::cout << json_like << std::endl;
    return true;
}

bool Parser::ParseField(const std::string& source) {
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

msgpack::object Parser::ParseCell(const std::string& source)
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

    msgpack::object_handle oh =
        msgpack::unpack(buffer.data(), buffer.size());

    std::string json_like;
    json_like_visitor v(json_like);
    std::size_t offset = 0;
    bool ret = msgpack::parse(buffer.data(), buffer.size(), offset, v);
    std::cout << json_like << std::endl;
    return oh.get();
}

Type Parser::Message() const { return type_; }
} // namespace core
} // namespace kr