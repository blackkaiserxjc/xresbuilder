#include <stdexcept>

#include "idl.h"
#include "idl_visitor.h"
#include "IDLLexer.h"
#include "IDLParser.h"

namespace kr
{
    namespace core
    {
        bool Parser::Parse(const std::string& source)
        {
            using namespace antlr4;
            ANTLRInputStream input(source);
            IDLLexer lexer(&input);
            CommonTokenStream tokens(&lexer);
            IDLParser parser(&tokens);

            IDLParseVisitor visitor;
            auto tree = parser.program();
            try
            {
                type_ = visitor.visitProgram(tree).as<Type>();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return false;
            }
            return true;
        }

        Type Parser::Message() const
        {
            return type_;
        }
    }
}