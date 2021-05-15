#include <iostream>

#include "antlr4-runtime.h"
#include "FieldLexer.h"
#include "FieldParser.h"

using namespace std;
using namespace antlr4;

void print()
{
    std::string str = "[int]";
    ANTLRInputStream input(str);
    FieldLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    FieldParser parser(&tokens);    

    auto tree = parser.prog(); 
    std::cout << tree->toStringTree(&parser, true) << std::endl;
}