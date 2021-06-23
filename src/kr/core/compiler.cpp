#include <filesystem>
#include <iostream>
#include <unordered_map>

#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <fmt/format.h>

#include <kr/core/compiler.h>
#include <kr/core/data_loader.h>
#include <kr/core/data_table.h>
#include <kr/core/generator_helpers.h>
#include <kr/core/model.h>

namespace fs = std::filesystem;

namespace kr {
namespace core {

int Compiler::run(int argc, char **argv)
{
    if (params_.generators == nullptr || params_.num_generators == 0)
    {
        return EXIT_FAILURE;
    }

    boost::program_options::options_description desc("Allowed options");
    auto &options = desc.add_options()("help", "produce help message")("src", boost::program_options::value<std::string>(), "data dictory")("dest", boost::program_options::value<std::string>(), "output dictory")("indent-step", boost::program_options::value<int>(), "code generator indent step")("filename-ext", boost::program_options::value<std::string>(), "filename extension")("field-naming-style", boost::program_options::value<std::string>(), "field naming style: camel or pascal")("filename-naming-style", boost::program_options::value<std::string>(), "filename naming style: camel or pascal")("folder-naming-style", boost::program_options::value<std::string>(), "folder naming style: camel or pascal");

    for (size_t index = 0; index < params_.num_generators; index++)
    {
        auto generator = params_.generators[index];
        options = options(generator.generator_opt, generator.generator_help);
    }

    boost::program_options::variables_map vm;
    boost::program_options::store(
        boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return EXIT_SUCCESS;
    }

    IDLOptions opts;
    if (vm.count("src"))
    {
        opts.src = vm["src"].as<std::string>();
    }
    if (vm.count("dest"))
    {
        opts.dest = vm["dest"].as<std::string>();
    }
    if (opts.src.empty() || opts.dest.empty())
    {
        std::cout << "src or dest is empty" << std::endl;
        return EXIT_FAILURE;
    }

    if (vm.count("indent-step"))
    {
        opts.indent_step = vm["indent-step"].as<int>();
    }

    if (vm.count("filename-ext"))
    {
        opts.extension = vm["filename-ext"].as<std::string>();
    }

    std::unordered_map<std::string, uint32_t> naming_styles = {
        {"camel", static_cast<uint32_t>(IDLOptions::NamingStyle::kCamelCase)},
        {"pascal", static_cast<uint32_t>(IDLOptions::NamingStyle::kPascalCase)}};
    if (vm.count("filename-naming-style"))
    {
        auto style = vm["filename-naming-style"].as<std::string>();
        if (naming_styles.count(style))
        {
            opts.filename_naming_style = naming_styles[style];
        }
    }

    if (vm.count("field-naming-style"))
    {
        auto style = vm["field-naming-style"].as<std::string>();
        if (naming_styles.count(style))
        {
            opts.field_naming_style = naming_styles[style];
        }
    }

    if (vm.count("folder-naming-style"))
    {
        auto style = vm["folder-naming-style"].as<std::string>();
        if (naming_styles.count(style))
        {
            opts.folder_naming_style = naming_styles[style];
        }
    }

    for (size_t index = 0; index < params_.num_generators; index++)
    {
        if (vm.count(params_.generators[index].generator_opt))
        {
            opts.lang_to_generate |= params_.generators[index].lang;
        }
    }

    try
    {
        generate(opts);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}

int Compiler::run_with_gui(const IDLOptions &opts)
{
    if (!opts.lang_to_generate)
    {
        error("lange opt is null");
        return EXIT_FAILURE;
    }

    if (opts.src_paths_.empty())
    {
        error("src paths is empty.");
        return EXIT_FAILURE;
    }

    fs::path src_path(opts.src);
    fs::path dest_path(opts.dest);
    if (!fs::exists(src_path) || !fs::is_directory(src_path))
    {
        error("src path not exists or not directory");
        return EXIT_FAILURE;
    }

    std::vector<std::string> full_paths;
    for (auto &&p : opts.src_paths_)
    {
        if (fs::is_regular_file(p))
        {
            full_paths.emplace_back(p);
        }
        else if (fs::is_directory(p))
        {
            for (auto &entry : fs::recursive_directory_iterator(p))
            {
                if (entry.is_regular_file())
                {
                    full_paths.emplace_back(entry.path().string());
                }
            }
        }
    }

    auto folder_naming_style = opts.folder_naming_style;
    auto generate_path = [&dest_path, &src_path,
                             folder_naming_style](auto &&cur_path) {
        auto gen_path = dest_path;
        auto relative_path = fs::relative(cur_path, src_path);
        if (folder_naming_style)
        {
            auto naming = [folder_naming_style](auto &&src) {
                auto result = src;
                switch (folder_naming_style)
                {
                case IDLOptions::kPascalCase: {
                    result = generator::underscores_to_pascalcase(src);
                }
                break;
                case IDLOptions::kCamelCase: {
                    result = generator::underscores_to_camelcase(src);
                }
                break;
                default:
                    break;
                }
                return result;
            };
            for (auto iter = relative_path.begin(); iter != relative_path.end();
                 ++iter)
            {
                auto p = iter->string();
                if (!(p.empty() || p == "/" || p == "\\"))
                {
                    gen_path /= naming(p);
                }
            }
        }
        else
        {
            gen_path /= relative_path;
        }
        return gen_path.parent_path();
    };

    auto generate_code = [&](auto &&src, auto &&dest, auto &&filename) {
        auto relative_src_path = fs::relative(src, src_path);
        auto relative_dest_path = fs::relative(dest, dest_path);
        debug("================================================================");
        debug(fmt::format("convert [{}] from [{}]", filename,
            relative_src_path.string()));
        DataTable dt("data table");
        if (!DataLoader::execute(src.string(), dt))
        {
            error("data load failed.");
            return;
        }

        Model model(dt);
        for (size_t index = 0; index < params_.num_generators; ++index)
        {
            auto &generator = params_.generators[index];
            if (generator.lang & opts.lang_to_generate)
            {
                generator.generate(model, opts, dest.string(), filename);
            }
        }
        debug(fmt::format("success.", src.string()));
    };

    std::for_each(full_paths.begin(), full_paths.end(), [&](auto &&value) {
        fs::path cur_path(value);
        auto code_path = generate_path(cur_path);
        if (!fs::exists(code_path))
        {
            fs::create_directories(code_path);
        }
        auto filename = cur_path.stem().string();
        try
        {
            generate_code(cur_path, code_path, filename);
        }
        catch (std::exception &e)
        {
            error(e.what());
        }
        catch (const char *e)
        {
            error(e);
        }
        catch (std::string e)
        {
            error(e);
        }
        catch (...)
        {
            error("Unhandled exception");
        }
    });

    return EXIT_SUCCESS;
}

void Compiler::generate(const IDLOptions &opts)
{
    if (!opts.lang_to_generate)
    {
        std::cout << "lange opt is null" << std::endl;
        return;
    }

    fs::path src_path(opts.src);
    fs::path dest_path(opts.dest);
    if (!fs::exists(src_path) || !fs::is_directory(src_path))
    {
        std::cout << "src path not exists or not directory" << std::endl;
        return;
    }

    std::vector<std::string> full_paths;
    for (auto &entry : fs::recursive_directory_iterator(opts.src))
    {
        if (entry.is_regular_file())
        {
            full_paths.emplace_back(entry.path().string());
        }
    }

    auto folder_naming_style = opts.folder_naming_style;
    auto generate_path = [&dest_path, &src_path,
                             folder_naming_style](auto &&cur_path) {
        auto gen_path = dest_path;
        auto relative_path = fs::relative(cur_path, src_path);
        if (folder_naming_style)
        {
            auto naming = [folder_naming_style](auto &&src) {
                auto result = src;
                switch (folder_naming_style)
                {
                case IDLOptions::kCamelCase: {
                    result = generator::underscores_to_camelcase(src);
                }
                break;
                case IDLOptions::kPascalCase: {
                    result = generator::underscores_to_pascalcase(src);
                }
                break;
                default:
                    break;
                }
                return result;
            };
            for (auto iter = relative_path.begin(); iter != relative_path.end();
                 ++iter)
            {
                auto p = iter->string();
                if (!(p.empty() || p == "/" || p == "\\"))
                {
                    gen_path /= naming(p);
                }
            }
        }
        else
        {
            gen_path /= relative_path;
        }
        return gen_path.parent_path();
    };

    auto generate_code = [&](auto &&src, auto &&dest, auto &&filename) {
        std::cout << "==================================================="
                  << std::endl;
        std::cout << fmt::format("load	  start:  path = {}", src.string())
                  << std::endl;
        DataTable dt("data table");
        if (!DataLoader::execute(src.string(), dt))
        {
            std::cout << "data load failed." << std::endl;
            return;
        }

        std::cout << fmt::format("generate start:  path = {}", src.string())
                  << std::endl;
        Model model(dt);
        for (size_t index = 0; index < params_.num_generators; ++index)
        {
            auto &generator = params_.generators[index];
            if (generator.lang & opts.lang_to_generate)
            {
                generator.generate(model, opts, dest.string(), filename);
            }
        }
        std::cout << fmt::format("generate finish: path = {}", src.string())
                  << std::endl;
    };

    std::for_each(full_paths.begin(), full_paths.end(), [&](auto &&value) {
        fs::path cur_path(value);
        auto code_path = generate_path(cur_path);
        if (!fs::exists(code_path))
        {
            fs::create_directories(code_path);
        }
        auto filename = cur_path.stem().string();
        try
        {
            generate_code(cur_path, code_path, filename);
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (const char *e)
        {
            std::cout << e << std::endl;
        }
        catch (std::string e)
        {
            std::cout << e << std::endl;
        }
        catch (...)
        {
            std::cout << "Unhandled exception" << std::endl;
        }
    });
}

void Compiler::warn(const std::string &warn)
{
    params_.warn_fn(warn);
}

void Compiler::error(const std::string &error)
{
    params_.error_fn(error);
}

void Compiler::debug(const std::string &debug)
{
    params_.debug_fn(debug);
};

} // namespace core
} // namespace kr
