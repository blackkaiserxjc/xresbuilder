#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace kr {
namespace core {

class DataColumnCollection;
class DataRow;
class DataRowCollection;
class DataTable;

template <typename T>
class TDataColumn
{
public:
    explicit TDataColumn(const std::string &name = {})
        : name_{name}
    {
    }
    virtual ~TDataColumn() {}

    void name(const std::string &value)
    {
        name_ = value;
    }
    
    std::string name() const { return name_; };

    void value(const T &value)
    {
        value_ = value;
    }

    T value() const { return value_; }

    DataTable *table() const { return table_; }

protected:
    std::string name_;
    T value_;
    DataTable *table_;
};

class DataColumn : public TDataColumn<std::string>
{
public:
    explicit DataColumn(const std::string &name = {});
    virtual ~DataColumn();

    DataColumn(const DataColumn&) = default;
    DataColumn& operator=(const DataColumn&) = default;
    DataColumn(DataColumn&&) = default;
    DataColumn& operator=(DataColumn &&) = default;

    std::string toString();

    friend class DataColumnCollection;
    friend class DataTable;
};

class DataColumnCollection
{
public: 
    explicit DataColumnCollection(DataTable* table);
    ~DataColumnCollection();

    void add(std::shared_ptr<DataColumn> column);
    void addAt(int index, std::shared_ptr<DataColumn> column);
    void addRange(const std::vector<std::shared_ptr<DataColumn>>& columns);
    std::shared_ptr<DataColumn> add(const std::string& name = {});

    bool contains(const std::string& name);
    void clear();
    size_t count();
    int indexOf(const std::string& name);

    void remove(const std::string& name);
    void removeAt(size_t index);

    DataColumn& operator[](size_t index);
    DataColumn& operator[](const std::string& name);
    
    friend class DataTable;
    friend class DataRow;
    friend class DataRowCollection;

private:
    DataTable *table_;
    std::vector<std::shared_ptr<DataColumn>> vec_;
    std::unordered_map<std::string, std::shared_ptr<DataColumn>> dict_;
};

class DataRow
{
public:
    int rowID() { return row_id_; }
    DataTable *table() const { return table_; }

    DataColumn& operator[](std::size_t column_index);
    DataColumn& operator[](const std::string& column_name);
    bool operator==(const DataRow& other);

    friend class DataTable;
    friend class DataRowCollection;
    friend class DataColumnCollection;

private:
    DataTable* table_;
    int row_id_;
    std::shared_ptr<DataColumn> columns_;
};

class DataRowCollection
{

};

}
}