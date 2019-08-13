#include "attributenode.h"

#include "../table.h"

namespace Ariel {

QString AttributeNode::name() const
{
    return data()->name;
}

QString AttributeNode::relation() const
{
    return data()->relation ? data()->relation->name : QString();
}

QExplicitlySharedDataPointer<UnqualifiedColumn> AttributeNode::toUnqualifideColumnNode() const
{
    return UnqualifiedColumn::create(data());
}


QString UnqualifiedColumn::name() const
{
    return data()->name;
}

AttributeNode::Pointer UnqualifiedColumn::toAttributeNode() const
{
    return AttributeNode::create(data());
}

} // namespace Ariel
