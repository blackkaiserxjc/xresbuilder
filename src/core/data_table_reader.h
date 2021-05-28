#ifndef KR_APP_CORE_DATA_TABLE_H_
#define KR_APP_CORE_DATA_TABLE_H_

#include <cstddef>
#include <iterator>

namespace kr {
namespace core {

// 特化标签
class CSVFormat {};
class XlsxFormat {};


class Row;
template <typename Format>
class DataTableReader 
{
public:
    class iterator
    {
    public:
        using value_type = Row;
        using difference_type = std::ptrdiff_t;
        using pointer = Row* ;
        using reference = Row&;
    };

    DataTableReader();
    virtual ~DataTableReader() {}

    bool empty() const;
    std::size_t columns() const;
    std::size_t rows() const;

    
};      

}
}

#include "detail/data_table_reader.h"

#endif
