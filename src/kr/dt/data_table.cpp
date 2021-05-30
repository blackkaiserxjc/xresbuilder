#include <dt/data_table.h>

namespace kr {
namespace dt {

data_table_iterator::data_table_iterator(DataTable* dt, const DataRow& cursor)
    : parent_(dt), cursor_(cursor)
{
}

data_table_iterator::reference data_table_iterator::operator *()
{
    return cursor_;
}

data_table_iterator::pointer data_table_iterator::operator ->()
{
    return &cursor_;
}

bool data_table_iterator::operator == (const data_table_iterator& other) const
{
    return parent_ == other.parent_ && cursor_ == other.cursor_;
}

bool data_table_iterator::operator != (const data_table_iterator&) const
{
    return !(*this == other)
} 

data_table_iterator& data_table_iterator::operator--()
{

}

data_table_iterator data_table_iterator::operator--(int)
{

}

data_table_iterator& data_table_iterator::operator++()
{

}

data_table_iterator data_table_iterator::operator(int)
{

}

data_table_iterator data_table_iterator::operator+ (difference_type n) const
{

}

data_table_iterator& data_table_iterator::operator +=(difference_type n)
{

}

data_table_iterator data_table_iterator::operator- (difference_type n) const
{

}

data_table_iterator& data_table_iterator::operator-= (difference_type n)
{

}

reference data_table_iterator::operator[](difference_type n) const
{
    
}

}
} // namespace kr
