#include <kr/core/model.h>

namespace kr {
namespace core {

Object::Object(const DataRow& data)
    :id_(data.id())
{
    init(data);
}

Object::~Object()
{
}

void Object::init(const DataRow& data)
{
    std::vector<std::string> fields;
    auto& columns = data.columns();
    for(auto index = 0; index < columns.count(); index++)
    {
        auto& column = columns[index];
    }
}

}
}