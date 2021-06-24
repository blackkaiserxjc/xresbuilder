#include <kr/core/parser.h>

namespace kr {
namespace core {

bool Parser::parse_field(const std::string &source, Type &type) {
  using namespace antlr4;
  ANTLRInputStream input(source);
  IDLLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  IDLParser parser(&tokens);
  parser.setErrorHandler(std::make_shared<ErrorStrategy>());
  
  IDLAstBuilder ast_builder;
  auto tree = parser.program();
  type = ast_builder.visitProgram(tree).as<Type>();
  return true;
}
} // namespace core
} // namespace kr