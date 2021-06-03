#include <filesystem>
#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <fmt/format.h>

#include <kr/core/compiler.h>
#include <kr/core/data_loader.h>
#include <kr/core/data_table.h>
#include <kr/core/model.h>

namespace fs = std::filesystem;

namespace kr {
namespace core {

int Compiler::run(int argc, char **argv) {
  if (params_.generators == nullptr || params_.num_generators == 0) {
    return EXIT_FAILURE;
  }

  boost::program_options::options_description desc("Allowed options");
  auto &options = desc.add_options()("help", "produce help message")(
      "src", boost::program_options::value<std::string>(), "data dictory")(
      "dest", boost::program_options::value<std::string>(), "generate dictory");

  for (size_t index = 0; index < params_.num_generators; index++) {
    auto generator = params_.generators[index];
    options = options(generator.generator_opt, generator.generator_help);
  }

  boost::program_options::variables_map vm;
  boost::program_options::store(
      boost::program_options::parse_command_line(argc, argv, desc), vm);
  boost::program_options::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return EXIT_SUCCESS;
  }

  Options opts;
  if (vm.count("src")) {
    opts.src = vm["src"].as<std::string>();
  }
  if (vm.count("dest")) {
    opts.dest = vm["dest"].as<std::string>();
  }
  if (opts.src.empty() || opts.dest.empty()) {
    std::cout << "src or dest is empty" << std::endl;
    return EXIT_FAILURE;
  }

  for (size_t index = 0; index < params_.num_generators; index++) {
    if (vm.count(params_.generators[index].generator_opt)) {
      opts.lang_to_generate |= params_.generators[index].lang;
    }
  }

  generate(opts);
  return EXIT_SUCCESS;
}

void Compiler::generate(const Options &opts) {
  if (!opts.lang_to_generate) {
    std::cout << "lange opt is null" << std::endl;
    return;
  }

  fs::path src_path(opts.src);
  fs::path dest_path(opts.dest);
  if (!fs::exists(src_path) || !fs::is_directory(src_path)) {
    std::cout << "src path not exists or not directory" << std::endl;
    return;
  }

  std::vector<std::string> full_paths;
  for (auto &p : fs::recursive_directory_iterator(opts.src)) {
    full_paths.emplace_back(p.path().string());
  }

  auto generate_path = [dest_path, &src_path](auto &&cur_path) {
    auto relative_path = fs::relative(cur_path, src_path);
    dest_path / relative_path;
    return dest_path;
  };

  auto generate_code = [&](auto &&src, auto &&dest, auto &&filename) {
    DataTable dt("data table");
    if (!DataLoader::execute(src.string(), dt)) {
      std::cout << "data load failed." << std::endl;
      return;
    }

    std::cout << fmt::format("generate start:  path ={}", src.string()) << std::endl;
    Model model(dt);
    for (size_t index = 0; index < params_.num_generators; ++index) {
      auto &generator = params_.generators[index];
      if (generator.lang & opts.lang_to_generate) {
        generator.generate(model, dest.string(), filename);
      }
    }
    std::cout << fmt::format("generate finish: path ={}", src.string()) << std::endl;
  };

  std::for_each(full_paths.begin(), full_paths.end(), [&](auto &&value) {
    fs::path cur_path(value);
    auto file_name = cur_path.stem().string();
    auto dest_path = generate_path(cur_path);
    if (!fs::exists(dest_path)) {
      fs::create_directories(dest_path);
    }
    generate_code(cur_path, dest_path, file_name);
  });
}
} // namespace core
} // namespace kr
