#include <algorithm>
#include <filesystem>

#include <boost/algorithm/string.hpp>
#include <fmt/format.h>
#include <xlnt/xlnt.hpp>

#include <kr/core/data_loader.h>
#include <kr/core/data_table.h>
#include <kr/core/rapidcsv.h>

namespace kr {
namespace core {

namespace detail {

enum class HeaderRowIndex {
  VALUE = 0,
  TYPE = 1,
  COMMENT = 2,
  START = 3,
};

struct HeaderField {
  explicit HeaderField(int index = 0, const std::string &value = {},
                       const std::string &type = {}, int begin_index = 0,
                       int end_index = 0)
      : index{index}, value{value}, type{type},
        begin_index{begin_index}, end_index{end_index} {}

  int index;
  std::string value;
  std::string type;
  int begin_index;
  int end_index;
};

void build_columns(DataTable &table, const std::vector<HeaderField> &fields) {
  std::for_each(fields.begin(), fields.end(), [&](auto &&field) {
    auto column = std::make_shared<kr::core::DataColumn>();
    column->name(field.value);
    column->index(field.index);
    column->value(field.type);
    table.columns().add(column);
  });
}

void build_row(DataTable &table, const std::vector<std::string> &row_data,
               const std::vector<HeaderField> &fields) {
  auto convert = [&](auto &&field) {
    auto begin_index = field.begin_index;
    auto end_index = field.end_index;
    if (boost::starts_with(field.type, "[")) {
      std::vector<std::string> results;
      for (auto index = begin_index; index != end_index; ++index) {
        auto cell_data = boost::algorithm::to_lower_copy(row_data[index]);
        if (!cell_data.empty() && cell_data != "null") {
          results.emplace_back(row_data[index]);
        }
      }
      return fmt::format("[{}]", fmt::join(results, ";"));
    } else if (!field.type.empty()) {
      return row_data[begin_index];
    }
    return std::string({});
  };

  auto row = table.new_row();
  std::for_each(fields.begin(), fields.end(), [&](auto &&field) {
    auto standard = convert(field);
    if (!standard.empty()) {
      (*row)[field.value].value(standard);
    }
  });
  table.rows().add(row);
}

void build_csv_rows(DataTable &table, const rapidcsv::Document &doc,
                    const std::vector<HeaderField> &fields) {
  auto n_rows = doc.GetRowCount();
  auto start_index = static_cast<std::uint32_t>(HeaderRowIndex::START);
  for (auto index = start_index; index < n_rows; index++) {
    auto row = doc.GetRow<std::string>(index);
    if (!row.empty()) {
      build_row(table, row, fields);
    }
  }
}

bool load_from_csv(const std::string &path, DataTable &table) {
  try {
    rapidcsv::Document doc(path, rapidcsv::LabelParams(-1, -1));
    if (doc.GetRowCount() < static_cast<std::uint32_t>(HeaderRowIndex::START)) {
      std::cout << "rows less start row index." << std::endl;
      return false;
    }
    auto type_row = doc.GetRow<std::string>(
        static_cast<std::uint32_t>(HeaderRowIndex::TYPE));
    auto value_row = doc.GetRow<std::string>(
        static_cast<std::uint32_t>(HeaderRowIndex::VALUE));
    if (type_row.empty() || value_row.empty() ||
        type_row.size() != value_row.size()) {
      std::cout << "type row or value row is empty." << std::endl;
      return false;
    }

    // 生成头信息
    std::vector<int> field_indexs;
    size_t size = type_row.size();
    for (size_t i = 0; i < size; i++) {
      if (!type_row[i].empty()) {
        field_indexs.push_back(i);
      }
    }
    std::vector<detail::HeaderField> fields;
    int field_index_size = field_indexs.size();
    for (auto i = 0; i < field_index_size; i++) {
      auto cur_index = field_indexs[i];
      auto next_index =
          (i == field_index_size - 1) ? size : (field_indexs[i + 1]);
      fields.emplace_back(i, value_row[cur_index], type_row[cur_index],
                          cur_index, next_index);
    }
    // 构建表头
    build_columns(table, fields);
    // 构建数据
    build_csv_rows(table, doc, fields);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return false;
  }
  return true;
}

void build_xlsx_rows(DataTable &table,
                     std::vector<std::vector<std::string>> &whole_sheet,
                     const std::vector<HeaderField> &fields) {
  auto n_rows = whole_sheet.size();
  auto start_index = static_cast<std::uint32_t>(HeaderRowIndex::START);
  for (auto index = start_index; index < n_rows; index++) {
    auto &row = whole_sheet[index];
    if (!row.empty()) {
      build_row(table, row, fields);
    }
  }
}

bool load_from_xlsx(const std::string &path, DataTable &table) {
  try {
    xlnt::workbook wb;
    wb.load(path);
    auto ws = wb.active_sheet();
    std::vector<std::vector<std::string>> whole_sheet;
    for (auto row : ws.rows(false)) {
      std::vector<std::string> signle_row;
      for (auto cell : row) {
        signle_row.push_back(cell.to_string());
      }
      whole_sheet.push_back(signle_row);
    }

    if (whole_sheet.size() <
        static_cast<std::uint32_t>(HeaderRowIndex::START)) {
      std::cout << "rows less start row index." << std::endl;
      return false;
    }

    auto &type_row =
        whole_sheet.at(static_cast<std::uint32_t>(HeaderRowIndex::TYPE));
    auto &value_row =
        whole_sheet.at(static_cast<std::uint32_t>(HeaderRowIndex::VALUE));
    if (type_row.empty() || value_row.empty() ||
        type_row.size() != value_row.size()) {
      std::cout << "type row or value row is empty." << std::endl;
      return false;
    }

    // 生成头信息
    std::vector<int> field_indexs;
    size_t size = type_row.size();
    for (size_t i = 0; i < size; i++) {
      if (!type_row[i].empty()) {
        field_indexs.push_back(i);
      }
    }
    std::vector<detail::HeaderField> fields;
    int field_index_size = field_indexs.size();
    for (auto i = 0; i < field_index_size; i++) {
      auto cur_index = field_indexs[i];
      auto next_index =
          (i == field_index_size - 1) ? size : (field_indexs[i + 1]);
      fields.emplace_back(i, value_row[cur_index], type_row[cur_index],
                          cur_index, next_index);
    }
    // 构建表头
    build_columns(table, fields);
    // 构建数据
    build_xlsx_rows(table, whole_sheet, fields);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return false;
  }
  return true;
}

} // namespace detail

bool DataLoader::execute(const std::string &path, DataTable &table) {
  std::filesystem::path fpath(path);
  try {
    if (!std::filesystem::exists(fpath) ||
        !std::filesystem::is_regular_file(fpath)) {
      std::cout << "path: " << path << " invaild." << std::endl;
      return false;
    }

    auto extension = fpath.extension().string();
    if (extension == ".csv") {
      return load_from_csv(path, table);
    } else if (extension == ".xlsx" || extension == ".xlsm") {
      return load_from_xlsx(path, table);
    }
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << e.what() << std::endl;
    return false;
  }
  return true;
}

bool DataLoader::load_from_csv(const std::string &path, DataTable &table) {
  return detail::load_from_csv(path, table);;
}

bool DataLoader::load_from_xlsx(const std::string &path, DataTable &table) {
  return detail::load_from_xlsx(path, table);

}

} // namespace core
} // namespace kr