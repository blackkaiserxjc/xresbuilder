#include "idl.h"
#include <stdexcept>

#include "IDLLexer.h"
#include "IDLParser.h"
#include "CellLexer.h"
#include "CellParser.h"
#include "ast_builder.h"

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
    CellAstBuilder<delctype(packer)> ast_builder{packer};

    auto tree = parser.program();
    ast_builder.visitProgram(tree);

    msgpack::object_handle oh = msgpack::unpack(buffer.data(), buffer.size());
    return true;
}

Type Parser::Message() const { return type_; }
} // namespace core
} // namespace kr