#include <iostream>

#include "antlr4-runtime.h"
#include "IDLLexer.h"
#include "IDLParser.h"

using namespace std;
using namespace antlr4;

void print()
{
    std::string str = "[int]";
    ANTLRInputStream input(str);
    IDLLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    IDLParser parser(&tokens);    

    auto tree = parser.prog(); 
    std::cout << tree->toStringTree(&parser, true) << std::endl;
}