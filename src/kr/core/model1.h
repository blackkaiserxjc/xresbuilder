#pragma once

#include <vector>
#include <string>
#include <map>

#include <kr/core/type.h>
#include <kr/core/data_table.h>

namespace kr{
namespace core {

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
    Type root_;
    // 数据集
    std::map<int, std::shared<>> data_;
};

}
} 