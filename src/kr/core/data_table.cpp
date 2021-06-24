#include <algorithm>
#include <cassert>

#include <fmt/core.h>

#include <kr/core/data_table.h>

namespace kr {
namespace core {

DataColumn::DataColumn(const std::string &name)
    : TDataColumn<std::string>(name)
{
}

DataColumn::~DataColumn()
{
}

std::string DataColumn::to_string() const
{
    return fmt::format("column name: {}, value: {}", name_, value_);
}

DataColumnCollection::DataColumnCollection(DataTable *table)
    : table_(table)
{
}

DataColumnCollection::~DataColumnCollection()
{
    clear();
}

void DataColumnCollection::add(std::shared_ptr<DataColumn> column)
{
    add(vec_.size(), column);
}

void DataColumnCollection::add(size_t index,
    std::shared_ptr<DataColumn> column)
{
    if (!column /*|| (column->table() != nullptr && column->table() == table_)*/)
    {
        return;
    }
    assert(index >= 0 && index <= vec_.size());
    column->table_ = table_;
    vec_.insert(vec_.begin() + index, column);
    dict_.emplace(column->name_, column);
}

std::shared_ptr<DataColumn> DataColumnCollection::add(const std::string &name)
{
    auto column = std::make_shared<DataColumn>(name);
    add(column);
    return column;
}

bool DataColumnCollection::contains(const std::string &name) const
{
    return dict_.find(name) != dict_.end();
}

void DataColumnCollection::clear()
{
    vec_.clear();
    dict_.clear();
}

std::optional<int> DataColumnCollection::index(const std::string &name)
{
    if (dict_.count(name))
    {
        auto result = std::find_if(vec_.begin(), vec_.end(), [&name](auto &&value) {
            return value->name_ == name;
        });
        if (result != vec_.end())
        {
            return std::distance(vec_.begin(), result);
        }
    }
    return std::nullopt;
}

size_t DataColumnCollection::count() const
{
    return vec_.size();
}

void DataColumnCollection::remove(const std::string &name)
{
    if (auto iter = dict_.find(name); iter != dict_.end())
    {
        auto result = std::find_if(vec_.begin(), vec_.end(), [&name](auto &&value) {
            return value->name_ == name;
        });

        if (result != vec_.end())
        {
            vec_.erase(result);
        }
        dict_.erase(iter);
    }
}

void DataColumnCollection::remove(size_t index)
{
    assert(index >= 0 && index < vec_.size());
    auto column = vec_.at(index);
    remove(column);
}

void DataColumnCollection::remove(std::shared_ptr<DataColumn> column)
{
    assert(column != nullptr);
    if (table_ != nullptr && table_->rows_.count() > 0)
    {
        std::size_t count = table_->rows_.count();
        for (std::size_t index = 0; index < count; index++)
        {
            remove(*(table_->rows_[index].columns_), index);
        }
    }
}

void DataColumnCollection::remove(DataColumnCollection &collect, size_t index)
{
    assert(index >= 0 && index < collect.vec_.size());
    auto viter = collect.vec_.begin() + index;
    if (viter == collect.vec_.end())
    {
        return;
    }

    if (auto iter = collect.dict_.find((*viter)->name());
        iter != collect.dict_.end())
    {
        collect.dict_.erase(iter);
    }
    collect.vec_.erase(viter);
}

void DataColumnCollection::copy(DataColumnCollection &collect, size_t index)
{
    assert(index >= 0 && index < vec_.size());
    while (index < vec_.size())
    {
        collect.add(std::make_shared<DataColumn>(*vec_[index++]));
    }
}

DataColumn &DataColumnCollection::operator[](size_t index)
{
    assert(index >= 0 && index < vec_.size());
    return *vec_[index];
}

DataColumn &DataColumnCollection::operator[](const std::string &name)
{
    auto iter = dict_.find(name);
    assert(iter != dict_.end());
    return *(iter->second);
}

DataRow::DataRow(int id, DataTable *table)
    : row_id_(id), table_(table)
{
    columns_ = std::make_shared<DataColumnCollection>(table);
}

DataRow::~DataRow()
{
}

void DataRow::remove(size_t index)
{
    columns_->remove(index);
}

DataColumnCollection &DataRow::columns()
{
    return *columns_;
}

DataColumn &DataRow::operator[](size_t index)
{
    return (*columns_)[index];
}

DataColumn &DataRow::operator[](const std::string &name)
{
    return (*columns_)[name];
}

bool DataRow::operator==(const DataRow &row)
{
    return row_id_ == row.row_id_;
}

DataRowCollection::DataRowCollection(DataTable *table)
    : table_(table)
{
}

DataRowCollection::~DataRowCollection()
{
    clear();
}

void DataRowCollection::add(std::shared_ptr<DataRow> row)
{
    rows_.emplace(row->id(), row);
}

void DataRowCollection::clear()
{
    rows_.clear();
}

size_t DataRowCollection::count() const
{
    return rows_.size();
}

void DataRowCollection::remove(size_t index)
{
    if (auto iter = rows_.find(index); iter != rows_.end())
    {
        rows_.erase(iter);
    }
}

void DataRowCollection::remove(std::shared_ptr<DataRow> row)
{
    remove(row->id());
}

DataRow &DataRowCollection::operator[](size_t index)
{
    if (auto iter = rows_.find(index); iter != rows_.end())
    {
        return *(iter->second);
    }
    else
    {
        throw "data table index not found";
    }
}

DataTable::DataTable(const std::string &name)
    : name_(name), rows_(this), columns_(this), next_row_id_(1)
{
}

DataTable::~DataTable()
{
}

DataColumnCollection &DataTable::columns()
{
    return columns_;
}

DataRowCollection &DataTable::rows()
{
    return rows_;
}

void DataTable::clear()
{
    rows_.clear();
    columns_.clear();
}

std::shared_ptr<DataRow> DataTable::new_row()
{
    auto row = std::make_shared<DataRow>(next_row_id_, this);
    columns_.copy(*row->columns_, 0);
    next_row_id_++;
    return row;
}

DataRow &DataTable::operator[](size_t index)
{
    assert(index >= 0 && index < rows_.count());
    return rows_[index];
}

} // namespace core
} // namespace kr
