#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
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

    void index(int index) 
    {
        index_ = index;
    }

    int index() const
    {
        return index_;
    }

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
    int index_;
    std::string name_;
    T value_;
    DataTable *table_;
};

class DataColumn : public TDataColumn<std::string>
{
public:
    explicit DataColumn(const std::string &name = {});
    ~DataColumn();

    DataColumn(const DataColumn&) = default;
    DataColumn& operator=(const DataColumn&) = default;
    DataColumn(DataColumn&&) = default;
    DataColumn& operator=(DataColumn &&) = default;

    std::string toString() const;

    friend class DataColumnCollection;
    friend class DataTable;
};

class DataColumnCollection
{
public: 
    explicit DataColumnCollection(DataTable* table = nullptr);
    ~DataColumnCollection();

    void add(std::shared_ptr<DataColumn> column);
    void add(size_t index, std::shared_ptr<DataColumn> column);
    std::shared_ptr<DataColumn> add(const std::string& name = {});

    bool contains(const std::string& name) const;
    void clear();
    size_t count() const;
    std::optional<int> index(const std::string& name);

    void remove(const std::string& name);
    void remove(size_t index);
    void remove(std::shared_ptr<DataColumn> column);

    void copy(DataColumnCollection& collect, size_t index);

    DataColumn& operator[](size_t index);
    DataColumn& operator[](const std::string& name);

private:
    friend class DataTable;
    friend class DataRow;
    friend class DataRowCollection;

    void remove(DataColumnCollection& collect, size_t index);

    DataTable *table_;
    std::vector<std::shared_ptr<DataColumn>> vec_;
    std::unordered_map<std::string, std::shared_ptr<DataColumn>> dict_;
};

class DataRow
{
public:
    DataRow(int id, DataTable* table);
    ~DataRow();

    DataRow(const DataRow&) = default;
    DataRow& operator=(const DataRow&) = default;
    DataRow(DataRow&&) = default;
    DataRow& operator=(DataRow &&) = default;

    int id() { return row_id_; }
    DataTable *table() const { return table_; }

    void remove(size_t index);

    DataColumnCollection& columns();
    DataColumn& operator[](std::size_t column_index);
    DataColumn& operator[](const std::string& column_name);
    bool operator==(const DataRow& other);

private:
    friend class DataTable;
    friend class DataRowCollection;
    friend class DataColumnCollection;

    DataTable* table_;
    int row_id_;
    std::shared_ptr<DataColumnCollection> columns_; 
    static volatile int row_count_;
};

class DataRowCollection
{
public:
    explicit DataRowCollection(DataTable *table);
    ~DataRowCollection();

    DataTable* table() { return table_; }

    void add(std::shared_ptr<DataRow> row);
    void clear();
    size_t count() const;
    void remove(std::shared_ptr<DataRow> row);
    void remove(size_t index);

    DataRow& operator[](size_t index);
private:
    friend class DataTable;
    friend class DataColumnCollection;

    DataTable *table_;
    std::map<int, std::shared_ptr<DataRow>> rows_;
};

class DataTable
{
public:
    explicit DataTable(const std::string& name = {});
    ~DataTable();

    DataColumnCollection& columns();
    DataRowCollection& rows();

    std::string name() const { return name_; }
    void clear();
    std::shared_ptr<DataRow> newRow();

    DataRow& operator[](size_t index);

private:
    friend class DataColumnCollection;
    friend class DataRowCollection;

    std::string name_;
    int next_row_id_;
    DataRowCollection  rows_;
    DataColumnCollection columns_;
};

}
}