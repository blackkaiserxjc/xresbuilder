#ifndef KR_APP_CORE_DATA_TABLE_H_
#define KR_APP_CORE_DATA_TABLE_H_

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

#include "rapidcsv.h"
#include "type.h"

namespace kr
{
    namespace core
    {
        class DataTable;
        class DataRow
        {
        public:
            DataRow();
            DataRow(DataTable *parent, int row_number);

            bool empty() const noexcept { return size() == 0; }
            size_t size() const noexcept { return cells_.size(); }

            template <class Archive>
            void serialize(Archive &ar);

            const std::string operator[](std::size_t n) const;
            operator std::vector<std::string>() const;

            friend class DataTable;

        protected:
            DataTable* parent_;
            int row_number_;
            std::vector<std::string> cells_;
        };

        class DataTable
        {
        public:
            enum class HeaderRowIndex 
            {
                VALUE   = 0,
                TYPE    = 1,
                COMMENT = 2,
                START   = 3,
            };

            explicit DataTable(const std::string& path = {});

            template <class Stream,
                      std::enable_if_t<std::is_base_of_v<std::istream, Stream>,
                                       int> = 0>
            DataTable(Stream &stream);

            DataTable(DataTable&&) = default;
            DataTable(const DataTable&) = delete;
            DataTable& operator=(DataTable&&) = default;
            DataTable& operator=(const DataTable&) = delete;
            ~DataTable();

            bool empty() const { return n_rows_ == 0; }
            Type type() const { return type_; }
            size_t n_rows() const { return n_rows_; }
            size_t n_cols() const { return n_cols_; }

            void load(const std::string& path);

            template <class Stream,
                      std::enable_if_t<std::is_base_of_v<std::istream, Stream>,
                                       int> = 0>
            void load(Stream &stream);
            void clear();

            template <typename Archive>
            void serialize(Archive &ar);

        private:
            // 数据读取
            void read_data(const std::string& path);
            // 数据读取
            void read_data(std::istream &stream);
            // 解析
            void parse();
            // 解析头
            void parse_header();
            // 解析行
            void parse_data();
            // reader
            rapidcsv::Document doc_;
            // 行数
            std::uint32_t n_rows_;
            // 列数
            std::uint32_t n_cols_;
            // 表结构
            Type type_;
            // 数据集
            std::unordered_map<int, std::shared_ptr<DataRow>> data_;   
        };
    }
}

#include "impl/data_table.h"

#endif