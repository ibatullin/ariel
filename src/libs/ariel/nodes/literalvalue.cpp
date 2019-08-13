#include "literalvalue.h"

#include <QDebug>

namespace Ariel {

NodePointer LiteralValue::valueNode(const QVariant &value)
{
    if (value.type() == QVariant::Type::Bool) {
        if (value.toBool())
            return True::create();
        else
            return False::create();
    } else {
        return LiteralValue::create(value);
    }
}

NodePointer LiteralValue::valueOrListNode(const QVariant &value)
{
    if (value.type() == QVariant::Type::StringList)
        return StringList::create(value.toStringList());
    else if (value.type() == QVariant::Type::List)
        return VariantList::create(value.toList());
    else
        return valueNode(value);
}

} // namespace Ariel

