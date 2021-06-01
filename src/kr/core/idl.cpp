#include "idl.h"
#include <stdexcept>

#include "IDLLexer.h"
#include "IDLParser.h"
#include "CellLexer.h"
#include "CellParser.h"
#include "ast_builder.h"
#include <kr/core/detail/ast_builder.h>

namespace kr {
namespace core {
bool parse_data(const std::string& source, Packer<msgpack::packer<msgpack::sbuffer>>& packer)
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
    try 
    {
        type = ast_builder.visitProgram(tree).as<Type>();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}
}
}
