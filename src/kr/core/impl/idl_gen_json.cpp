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

class JsonVisitor : public msgpack::null_visitor 
{
public:
    JsonVisitor(CodeWriter& writer)
        : writer_(writer) 
    {}

    bool visit_nil() 
    {
        writer_ += "null";
        return true;
    }

    bool visit_boolean(bool v) 
    {
        if (v)
        {
            writer_ += "true";
        }
        else 
        {
            writer_ += "false";
        }
        return true;
    }

    bool visit_positive_integer(uint64_t v) 
    {
        writer_ += std::to_string(v);
        return true;
    }

    bool visit_negative_integer(int64_t v) 
    {
        writer_ += std::to_string(v);
        return true;
    }
    
    bool visit_float32(float v) 
    {
        writer_ += std::to_string(v);
        return true;
    }

    bool visit_float64(double v)
    {
        writer_ += std::to_string(v);
        return true;
    }

    bool visit_str(const char* v, uint32_t size) 
    {
        writer_ += '"' + std::string(v, size) + '"';
        return true;
    }
    
    bool start_array(uint32_t num_elements) 
    {
        current_size_.push_back(num_elements);
        writer_ += "[";
        return true;
    }
    
    bool end_array_item() 
    {
        --current_size_.back();
        if (current_size_.back() != 0)
        {
            writer_ += ",";
        }
        return true;
    }
    
    bool end_array() 
    {
        current_size_.pop_back();
        writer_ += "]";
        return true;
    }
    
    bool start_map(uint32_t num_kv_pairs) 
    {
        current_size_.push_back(num_kv_pairs);
        writer_ += "{";
        return true;
    }
    
    bool end_map_key() 
    {
        writer_ += ":";
        return true;
    }
    
    bool end_map_value() 
    {
        --current_size_.back();
        if (current_size_.back() != 0)
        {
            writer_ += ",";
        }
        return true;
    }

    bool end_map() 
    {   
        current_size_.pop_back();
        writer_ += "}";
        return true;
    }

private:
    CodeWriter& writer_;
    std::vector<uint32_t> current_size_;
};

class JsonGenerator : public CodeGenerator {
public:
    JsonGenerator(Model& model, const std::string& path, const std::string& file_name)
        : CodeGenerator(model, path, file_name)
    {}

    bool generate() override
    {   
        code_.clear();
        msgpack::sbuffer buffer;
        kr::core::Packer<msgpack::packer<msgpack::sbuffer>> packer{buffer};
        model_.serialize(packer);
    
        std::size_t offset = 0;
        JsonVisitor visitor(code_);
        msgpack::parse(buffer.data(), buffer.size(), offset, visitor);

        const std::string file_path = jsons::generated_filename(path_, file_name_);
        const std::string final_code = code_.to_string();
        return kr::utility::save_file(file_path.c_str(), final_code, false);
    }
private:
    CodeWriter code_;
};

bool generate_json(Model& model, const std::string& path, const std::string& file_name)
{
    JsonGenerator generator(model, path, file_name);
    return generator.generate();
}

}
}