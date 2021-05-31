#pragma once

#include <vector>
#include <string>
#include <map>

#include <msgpack.hpp>

#include <kr/core/type.h>
#include <kr/core/data_table.h>

namespace kr{
namespace core {

class Object
{
public:
    Object(int id, const DataRow& data);
    ~Object();

    template <typename Archive>
    void serialize(Archive& ar);

    int id() const { return id_; }
    std::string toString() const { return value_; }
    
protected:
    void init(const DataRow& data);

    int id_;
    std::string value_;
    msgpack::sbuffer buffer_;
};

class Model
{
public:
    explicit Model(const DataTable& table);

    Model(const Model& other) = delete;
    Model& operator=(const Model& other) = delete;
    Model(DataTable& other) = default;
    Model& operator=(Model&& other) = default;
    
    ~Model();
    
private:
    // 表结构
    Type type_;
    // 数据集
    std::map<int, std::shared<Object>> data_;
};

}
} 