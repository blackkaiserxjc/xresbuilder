#include <kr/core/parser.h>

namespace kr {
namespace core {

bool Parser::parse_field(const std::string &source, Type &type) {
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
} // namespace core
} // namespace kr