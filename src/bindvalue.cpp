#include "bindvalue.h"

namespace Ariel {

BindValue::BindValue(const QVariant &value)
    : d(new BindValueData(value))
{
}

BindValue::BindValue(const BindValueData::Pointer &d)
    : d(d)
{
}

void BindValue::setValue(const QVariant &value)
{
    d->value = value;
}

QVariant BindValue::value() const
{
    return d->value;
}

void BindValue::detach()
{
    d.detach();
}

BindValueNode::Pointer BindValue::toNode() const
{
    return BindValueNode::create(d);
}

bool BindValue::isValid() const
{
    return d->value.isValid();
}

bool BindValue::isNull() const
{
    return d->value.isNull();
}

} // namespace Ariel
