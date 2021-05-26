#include <iostream>
#include <string>
#include <sstream>

#include "core/idl.h"
#include "core/csv.hpp"

void csv_test()
{
  CSVFormat format;
  format.no_header()
      .trim({ '\t', ' ' })
      .delimiter(',');
  csv::CSVReader reader("/home/alien/doc/1.csv", format);
  std::stringstream my_json;

  for (auto value : reader.get_col_names())  {
    std::cout << "coliseum: " << value << std::endl;
  }

  for (auto& row: reader) {
      std::vector<std::string> line = row;
      for (auto value : line ) {
        std::cout << value << ',';
      }
      std::cout << std::endl;
  }
  std::cout << my_json.str() << std::endl;
}

int main(int argc, const char *argv[]) {
  csv_test();
  /*
  kr::core::Parser parser;
  parser.Parse("[x:int,y:int, value:[id:int, count:int]]", "20001,200,[2000,100;2001,102;2002,1003;2004,1004]");
  */
  //parser.Parse("[value:bool,goods:[id:int,count:int,x:string]]");
  //parser.ParseCell(
  //  "true,3.1415926,[120,\"hello world\";2001,\"x\",[20;21;22;23]]");
  return 0;
}
