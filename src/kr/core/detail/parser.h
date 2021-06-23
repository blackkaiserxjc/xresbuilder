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
    try
    {
        CellAstBuilder ast_builder{packer};
        ast_builder.visitProgram(parser.program());
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}
} // namespace core
} // namespace kr