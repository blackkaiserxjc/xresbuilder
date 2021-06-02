#include <iostream>

#include <kr/core/compiler.h>

/*
void data_loader_test()
{
    using namespace kr::core;
    DataTable dt("data table");
    if (DataLoader::execute("/home/alien/doc/3.csv", dt))
    {
        Model model(dt);
        generate_json(model, "/home/alien/doc/", "json_test");
        generate_lua(model, "/home/alien/doc/", "lua_test");
    }
}*/

int main(int argc, char **argv) {
  using namespace kr::core;
  const Compiler::Generator generators[] = {
      {generate_json, "json", "Json", Compiler::Options::kJson,
       "Generate Json schema"},
      {generate_lua, "lua", "Lua", Compiler::Options::kLua,
       "Generate Lua files"}};

  Compiler::InitParams init_params;
  init_params.generators = generators;
  init_params.num_generators = sizeof(generators) / sizeof(generators[0]);
  Compiler compiler(init_params);
  return compiler.run(argc, argv);
}
