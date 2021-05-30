#pragma once

#include <cstddef>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

#include <kr/dt/data_row.h>

namespace kr {
namespace dt {

class DataRow;
class DataTable;

class DataTableIterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = DataRow;
    using difference_type = std::ptrdiff_t;
    using pointer = DataRow *;
    using reference = DataRow&;

    DataTableIterator() = default;
    DataTableIterator(DataTable *dt, const DataRow& cursor);
    
    DataTableIterator(const DataTableIterator& ) = default;
    DataTableIterator& operator=(const DataTableIterator& ) = default;
    DataTableIterator(DataTableIterator&&) = default;
    DataTableIterator& operator=(const DataTableIterator& ) = default;

    ~DataTableIterator();

    reference operator*() const;
    pointer operator->() const;

    bool operator==(const DataTableIterator& other) const;           
    bool operator!=(const DataTableIterator& other) const;

    DataTableIterator& operator--();
    DataTableIterator operator--(int);
    DataTableIterator& operator++();
    DataTableIterator operator++(int);

    DataTableIterator  operator+ (difference_type n) const;
    DataTableIterator& operator+=(difference_type n);
    DataTableIterator  operator- (difference_type n) const;
    DataTableIterator& operator-=(difference_type n);

    reference operator[](difference_type n) const;

private:
    DataTable*  parent_
    DataRow     cursor_;
};

class DataTable
{
public:
    using iterator = DataTableIterator;
    using reverse_iterator = std::reverse_iterator<iterator>;

    explicit DataTable()
    {}

    iterator begin();
    iterator end();

private:
    
    std::string name;
    
};

} 
} 
