#include "bindvalue.h"

namespace Ariel {

BindValueData::BindValueData(const QVariant &value)
    : value(value)
{
}


BindValueNode::BindValueNode(BindValueData::Pointer d)
    : d(d)
{
}

BindValueNode::BindValueNode(const BindValueNode &other)
    : d(other.d)
{
    d.detach();
}

BindValueNode &BindValueNode::operator =(BindValueNode other)
{
    qSwap(d, other.d);
    d.detach();
    return *this;
}

void BindValueNode::setValue(const QVariant &value)
{
    d->value = value;
}

QVariant BindValueNode::value() const
{
    return d->value;
}

} // namespace Ariel
