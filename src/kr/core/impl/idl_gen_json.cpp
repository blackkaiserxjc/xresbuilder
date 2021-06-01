#include <fmt/format.h>

#include <kr/core/code_generator.h>
#include <kr/core/idl.h>
#include <kr/utility/utility.h>

namespace kr {
namespace core {
namespace jsons {

std::string generated_filename(const std::string& path, const std::string& file_name)
{
    return fmt::format("{}{}.json", path, file_name);
}

}

struct JsonVisitor : msgpack::null_visitor 
{
    JsonVisitor(std::string& str)
        : str_(str) 
    {}

    bool visit_nil() 
    {
        str_ += "null";
        return true;
    }

    bool visit_boolean(bool v) 
    {
        if (v)
        {
            str_ += "true";
        }
        else 
        {
            str_ += "false";
        }
        return true;
    }
    bool visit_positive_integer(uint64_t v) 
    {
        str_ += std::to_string(v);
        return true;
    }
    bool visit_negative_integer(int64_t v) {
        str_ += std::to_string(v);
        return true;
    }
    
    bool visit_float32(float v) 
    {
        str_ += std::to_string(v);
        return true;
    }

    bool visit_float64(double v)
    {
        str_ += std::to_string(v);
        return true;
    }

    bool visit_str(const char* v, uint32_t size) 
    {
        str_ += '"' + std::string(v, size) + '"';
        return true;
    }
    
    bool start_array(uint32_t num_elements) 
    {
        str_ += "[";
        return true;
    }
    
    bool end_array_item() 
    {
        str_ += ",";
        return true;
    }
    
    bool end_array() 
    {
        str_.erase(str_.size() - 1, 1); 
        str_ += "]";
        return true;
    }
    
    bool start_map(uint32_t num_kv_pairs) 
    {
        str_ += "{";
        return true;
    }
    
    bool end_map_key() 
    {
        str_ += ":";
        return true;
    }
    
    bool end_map_value() 
    {
        str_ += ",";
        return true;
    }

    bool end_map() 
    {
        str_.erase(str_.size() - 1, 1);
        str_ += "}";
        return true;
    }

    std::string& str_;
};

class JsonGenerator : public CodeGenerator {
public:
    JsonGenerator(Model& model, const std::string& path, const std::string& file_name)
        : CodeGenerator(model, path, file_name)
    {}

    bool generate() override
    {   
        msgpack::sbuffer buffer;
        kr::core::Packer<msgpack::packer<msgpack::sbuffer>> packer{buffer};
        model_.serialize(packer);

        std::string json;
        std::size_t offset = 0;
        JsonVisitor visitor(json);
        msgpack::parse(buffer.data(), buffer.size(), offset, visitor);

        const std::string file_path = jsons::generated_filename(path_, file_name_);
        const std::string final_code = json;
        return kr::utility::save_file(file_path.c_str(), final_code, false);
    }
private:
    CodeWriter writer_;
};

bool generate_json(Model& model, const std::string& path, const std::string& file_name)
{
    JsonGenerator generator(model, path, file_name);
    return generator.generate();
}

}
}