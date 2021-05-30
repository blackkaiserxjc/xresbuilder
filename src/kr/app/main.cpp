#include <iostream>
#include <string>
#include <sstream>

#include <msgpack.hpp>

#include <core/idl.h>
#include <core/pack.h>
#include <core/data_table.h>

void csv_test()
{ 
    kr::core::DataTable dt("/home/alien/doc/1.csv");
    msgpack::sbuffer buffer;
    kr::core::Packer<msgpack::packer<msgpack::sbuffer>> packer{buffer};
    dt.serialize(packer);

    std::string json_like;
    json_like_visitor v(json_like);
    std::size_t offset = 0;
    bool ret = msgpack::parse(buffer.data(), buffer.size(), offset, v);
    std::cout << json_like << std::endl;
    std::cout << dt.n_rows() << ":" << dt.n_cols() << std::endl;
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
