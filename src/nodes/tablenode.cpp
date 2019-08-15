#include "tablenode.h"

namespace Ariel {

TableNode::TableNode()
    : d(new TableData)
{
}

TableNode::TableNode(TableData::Pointer d)
    : d(d)
{
}

TableNode::TableNode(const TableNode &other)
    : d(other.d)
{
    d.detach();
}

TableNode &TableNode::operator =(TableNode other)
{
    std::swap(d, other.d);
    d.detach();
    return *this;
}

QString TableNode::name() const
{
    return d->name;
}

TableData::Pointer TableNode::data() const
{
    return d;
}

} // namespace Ariel
