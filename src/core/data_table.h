#ifndef KR_APP_CORE_DATA_TABLE_H_
#define KR_APP_CORE_DATA_TABLE_H_

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "rapidcsv.h"
#include "type.h"
#include "object_pack.h"

namespace kr
{
    namespace core
    {
        class DataTable;
        class DataRow
        {
        public:
            explicit DataRow(DataTable *parent = nullptr, int row_number = 0, const std::vector<std::string>& row = {});
            ~DataRow();

            msgpack::sbuffer& buffer() { return buffer_; };

            template <class Archive>
            void serialize(Archive &ar);

            friend class DataTable;
        protected:
            void convert(const std::vector<std::string>& row);

            DataTable* parent_;
            int row_number_;
            msgpack::sbuffer buffer_;
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

            /*
            template <class Stream,
                      std::enable_if_t<std::is_base_of_v<std::istream, Stream>,
                                       int> = 0>
            DataTable(Stream &stream);
            */

            DataTable(DataTable&&) = default;
            DataTable(const DataTable&) = delete;
            DataTable& operator=(DataTable&&) = default;
            DataTable& operator=(const DataTable&) = delete;
            ~DataTable();

            bool empty() const { return n_rows_ == 0; }
            Type type() const { return root_type_; }
            size_t n_rows() const { return n_rows_; }
            size_t n_cols() const { return n_cols_; }

            void load(const std::string& path);

            /*
            template <class Stream,
                      std::enable_if_t<std::is_base_of_v<std::istream, Stream>,
                                       int> = 0>
            void load(Stream &stream);
            */
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
            bool parse_header();
            // 解析行
            bool parse_data();
            // reader
            rapidcsv::Document doc_;
            // 行数
            std::uint32_t n_rows_;
            // 列数
            std::uint32_t n_cols_;
            // 表结构
            Type root_type_;
            // 数据集
            std::map<int, std::shared_ptr<DataRow>> data_;   
        };
        
        template<typename Archive>
        void DataRow::serialize(Archive &ar)
        {
            msgpack::object_handle oh = msgpack::unpack(buffer_.data(), buffer_.size());
            UnPacker<msgpack::object> unpakcer(oh.get());
            pack(ar, parent_->type(), unpakcer); 
        }

        template <typename Archive>
        void DataTable::serialize(Archive &ar)
        {   
            ar.pack_begin_array(data_.size());
            for(auto&& [key, row] : data_)
            {
                row->serialize(ar);
            }
            ar.pack_end_array();
        }
    }
}

#endif