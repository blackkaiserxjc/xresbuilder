#include <stdexcept>

namespace kr {
namespace core {

template <typename Packer>
bool Parser::parse_object(const std::string &source, Packer &packer)
{
    using namespace antlr4;
    ANTLRInputStream input(source);
    CellLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CellParser parser(&tokens);
    parser.setErrorHandler(std::make_shared<ErrorStrategy>());

    CellAstBuilder ast_builder{packer};
    ast_builder.visitProgram(parser.program());
    return true;
}
} // namespace core
} // namespace kr