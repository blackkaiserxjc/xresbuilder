#pragma once

#include "antlr4-runtime.h"

#include <map>
#include <string>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <msgpack.hpp>

#include <kr/core/data_table.h>
#include <kr/core/object_pack.h>
#include <kr/core/pack.h>
#include <kr/core/type.h>


namespace kr {
namespace core {

class Parser;
class Model;
class Object
{
public:
    Object(Model &model, DataRow &data);
    ~Object();

    template <typename Archive>
    void serialize(Archive &ar);

    int id() const
    {
        return id_;
    }
    std::string to_string() const
    {
        return value_;
    }

protected:
    friend class Model;
    void init(DataRow &data);
    void pack_buffer(const std::string &source);

    int id_;
    Model &model_;
    std::string value_;
    msgpack::sbuffer buffer_;
};

class Model : public boost::noncopyable
{
public:
    explicit Model(DataTable &table);
    ~Model();

    template <typename Archive>
    void serialize(Archive &ar);

    Type type() const
    {
        return table_def_;
    }

    std::shared_ptr<Parser> parser() const
    {
        return parser_;
    };

private:
    // 解析
    void parse(DataTable &table);
    // 解析table结构
    void parse_table_def(DataTable &table);
    // 解析数据
    void parse_table_data(DataTable &table);
    // 解析key index
    void parse_table_ki(std::shared_ptr<FieldDef> field_def, uint32_t base_type,
        uint32_t field_index, const std::string &name);
    // 解析器
    std::shared_ptr<Parser> parser_;
    // 表结构
    Type table_def_;
    // 数据集
    std::map<int, std::shared_ptr<Object>> data_;
};

template <typename Archive>
void Object::serialize(Archive &ar)
{
    ObjectPacker obj;
    try
    {
        msgpack::object_handle oh = msgpack::unpack(buffer_.data(), buffer_.size());
        UnPacker<msgpack::object> unpacker(oh.get());
        obj.pack(ar, model_.type(), unpacker);
    }
    catch(const std::exception& e)
    {   
        throw fmt::format("compile error: row = {}, field = {}, {}.", id_, obj.ctx().field, e.what());
    }
}

template <typename Archive>
void Model::serialize(Archive &ar)
{
    ar.pack_begin_array(data_.size());
    for (auto &&[key, object] : data_)
    {
        object->serialize(ar);
    }
    ar.pack_end_array();
}

} // namespace core
} // namespace kr