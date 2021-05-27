#ifndef KR_APP_CORE_DATA_SOURCE_H_
#define KR_APP_CORE_DATA_SOURCE_H_

#include <string>
#include <vector>

namespace kr {
namespace core {

enum class SourceType
{
    NONE    = 0,
    CSV     = 1,
    XLSX    = 2,
};


class DataSource 
{
public:
    using Row = std::vector<std::string>;
    
    DataSource(SourceType type, const std::string& path) 
        : type_(type), path_(path)
    {}
    virtual ~DataSource() {}

    SourceType type() const { return type_; }
    std::string path() const { return path_; }

    virtual std::size_t rows() const = 0;
    virtual std::size_t cols() const = 0;
protected:
    SourceType type_;
    std::string path_;  
};


}
}

#endif /* KR_APP_CORE_DATA_SOURCE */