#include <iostream>
#include <string>
#include <sstream>

#include <msgpack.hpp>

#include <kr/core/idl.h>
#include <kr/core/pack.h>
#include <kr/core/model.h>
#include <kr/core/data_table.h>
#include <kr/core/data_loader.h>

/*
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
}*/

void csv_test()
{
    using namespace kr::core;
    DataTable dt("data table");

    auto c1 = std::make_shared<DataColumn>();
    c1->name("c1");
    c1->value("int32");

    std::cout << c1->toString() << std::endl;
    dt.columns().add(c1);

    auto r1 = dt.newRow();
    (*r1)["c1"].value("1213131");
    dt.rows().add(r1);
}

void data_loader_test()
{
    using namespace kr::core;
    DataTable dt("data table");
    /*
    DataLoader::load_from_csv("/home/alien/doc/2.csv", dt);

    Model model(dt);
    generate_json(model, "/home/alien/doc/", "json_test");
    generate_lua(model, "/home/alien/doc/", "lua_test");
    */

    std::string path = "/home/kaiser/Documents/2.csv";
    std::string dir = "/home/kaiser/Documents/";
    DataLoader::load_from_csv(path, dt);
    Model model(dt);
    generate_json(model, dir, "json_test");
    generate_lua(model, dir, "lua_test");

    /*
    Model model(dt);
    msgpack::sbuffer buffer;
    kr::core::Packer<msgpack::packer<msgpack::sbuffer>> packer{buffer};
    model.serialize(packer);


    std::string json_like;
    json_like_visitor v(json_like);
    std::size_t offset = 0;
    bool ret = msgpack::parse(buffer.data(), buffer.size(), offset, v);
    std::cout << json_like << std::endl;
    */
    //DataLoader::LoadFromCSV("/home/kaiser/Documents/1.csv", dt);
} 

int main(int argc, const char *argv[]) {
  csv_test();
  data_loader_test();
  /*
  kr::core::Parser parser;
  parser.Parse("[x:int,y:int, value:[id:int, count:int]]", "20001,200,[2000,100;2001,102;2002,1003;2004,1004]");
  */
  //parser.Parse("[value:bool,goods:[id:int,count:int,x:string]]");
  //parser.ParseCell(
  //  "true,3.1415926,[120,\"hello world\";2001,\"x\",[20;21;22;23]]");
  return 0;
}
