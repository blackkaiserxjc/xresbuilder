#include <iostream>
#include <string>

#include <core/idl.h>

int main(int argc, const char* argv[]) 
{  
    kr::core::Parser parser;
    parser.Parse("[value:bool,goods:[id:int,count:int,x:string]]");
    parser.ParseCell("true,3.1415926,[120,\"hello world\";2001,\"x\",[20;21;22;23]]");
    return 0;
}

    