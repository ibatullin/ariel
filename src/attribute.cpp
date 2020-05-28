#include "attribute.h"

#include "table.h"
#include "bindvalue.h"

namespace Ariel {

Attribute::Attribute(const QString &name, const TableData::Pointer &relation)
    : d(new AttributeData)
{
    d->name = name;
    d->relation = relation;
}

Attribute::Attribute(const AttributeData::Pointer &d)
    : d(d)
{
}

void Attribute::setName(const QString &name)
{
    d->name = name;
}

QString Attribute::name() const
{
    return d->name;
}

Table Attribute::relation() const
{
    return Table(d->relation);
}

Ascending::Pointer Attribute::ascending() const
{
    auto node = Ascending::create();
    node->setExpression(toNode());
    return node;
}

Descending::Pointer Attribute::descending() const
{
    auto node = Descending::create();
    node->setExpression(toNode());
    return node;
}

SpecialComparisonOperator Attribute::between(const QVariant &value1, const QVariant &value2) const
{
    const auto lhs = LiteralValue::create(value1);
    const auto rhs = LiteralValue::create(value2);
    return SpecialComparisonOperator::between(toNode(), lhs, rhs);
}

SpecialComparisonOperator Attribute::match(const QString &pattern) const
{
    return SpecialComparisonOperator::matches(toNode(), LiteralValue::create(pattern));
}

SpecialComparisonOperator Attribute::in(const QVariant &value) const
{
    return SpecialComparisonOperator::in(toNode(), LiteralValue::valueOrListNode(value));
}

SpecialComparisonOperator Attribute::notIn(const QVariant &value) const
{
    return SpecialComparisonOperator::notIn(toNode(), LiteralValue::valueOrListNode(value));
}

SpecialComparisonOperator Attribute::isNull() const
{
    return SpecialComparisonOperator::isNull(toNode());
}

SpecialComparisonOperator Attribute::isNotNull() const
{
    return SpecialComparisonOperator::isNotNull(toNode());
}

Max::Pointer Attribute::max() const
{
    return Max::create(toNode());
}

Min::Pointer Attribute::min() const
{
    return Min::create(toNode());
}

AttributeNode::Pointer Attribute::toNode() const
{
    return AttributeNode::create(d);
}

UnqualifiedColumn::Pointer Attribute::toUnqualifiedColumn() const
{
    return UnqualifiedColumn::create(d);
}



ComparisonOperator operator ==(const Attribute &attribute, const QVariant &value)
{
    if (!value.isValid() || value.isNull()) {
        return attribute.isNull();
    } else {
        const NodePointer lhs = attribute.toNode();
        const NodePointer rhs = LiteralValue::valueNode(value);
        return ComparisonOperator::equal(lhs, rhs);
    }
}

ComparisonOperator operator ==(const Attribute &attribute, const BindValue &value)
{
    auto lhs = attribute.toNode();
    auto rhs = value.toNode();
    return ComparisonOperator::equal(lhs, rhs);
}

ComparisonOperator operator ==(const Attribute &attribute, const QStringList &list)
{
    return attribute.in(list);
}

ComparisonOperator operator ==(const Attribute &attribute, const QVariantList &list)
{
    return attribute.in(list);
}

ComparisonOperator operator !=(const Attribute &attribute, const QVariant &value)
{
    const NodePointer lhs = attribute.toNode();
    const NodePointer rhs = LiteralValue::valueNode(value);
    return ComparisonOperator::notEqual(lhs, rhs);
}

ComparisonOperator operator !=(const Attribute &attribute, const QStringList &list)
{
    return attribute.notIn(list);
}

ComparisonOperator operator !=(const Attribute &attribute, const QVariantList &list)
{
    return attribute.notIn(list);
}

ComparisonOperator operator >(const Attribute &attribute, const QVariant &value)
{
    const auto lhs = attribute.toNode();
    const auto rhs = LiteralValue::create(value);
    return ComparisonOperator::greaterThan(lhs, rhs);
}

ComparisonOperator operator >=(const Attribute &attribute, const QVariant &value)
{
    const auto lhs = attribute.toNode();
    const auto rhs = LiteralValue::create(value);
    return ComparisonOperator::greaterThanOrEqual(lhs, rhs);
}

ComparisonOperator operator <(const Attribute &attribute, const QVariant &value)
{
    const auto lhs = attribute.toNode();
    const auto rhs = LiteralValue::create(value);
    return ComparisonOperator::lessThan(lhs, rhs);
}

ComparisonOperator operator <=(const Attribute &attribute, const QVariant &value)
{
    const auto lhs = attribute.toNode();
    const auto rhs = LiteralValue::create(value);
    return ComparisonOperator::lessThanOrEqual(lhs, rhs);
}


ComparisonOperator operator ==(const Attribute &lhs, const Attribute &rhs)
{
    return ComparisonOperator::equal(lhs.toNode(), rhs.toNode());
}

ComparisonOperator operator !=(const Attribute &lhs, const Attribute &rhs)
{
    return ComparisonOperator::notEqual(lhs.toNode(), rhs.toNode());
}

ComparisonOperator operator >(const Attribute &lhs, const Attribute &rhs)
{
    return ComparisonOperator::greaterThan(lhs.toNode(), rhs.toNode());
}

ComparisonOperator operator >=(const Attribute &lhs, const Attribute &rhs)
{
    return ComparisonOperator::greaterThanOrEqual(lhs.toNode(), rhs.toNode());
}

ComparisonOperator operator <(const Attribute &lhs, const Attribute &rhs)
{
    return ComparisonOperator::lessThan(lhs.toNode(), rhs.toNode());
}

ComparisonOperator operator <=(const Attribute &lhs, const Attribute &rhs)
{
    return ComparisonOperator::lessThanOrEqual(lhs.toNode(), rhs.toNode());
}


ComparisonOperator operator !(const Attribute &attribute)
{
    return attribute == false;
}

ComparisonOperator operator !=(const Attribute &attribute, const BindValue &value)
{
    auto lhs = attribute.toNode();
    auto rhs = value.toNode();
    return ComparisonOperator::notEqual(lhs, rhs);
}

ComparisonOperator operator >(const Attribute &attribute, const BindValue &value)
{
    auto lhs = attribute.toNode();
    auto rhs = value.toNode();
    return ComparisonOperator::greaterThan(lhs, rhs);
}

ComparisonOperator operator >=(const Attribute &attribute, const BindValue &value)
{
    auto lhs = attribute.toNode();
    auto rhs = value.toNode();
    return ComparisonOperator::greaterThanOrEqual(lhs, rhs);
}

ComparisonOperator operator <(const Attribute &attribute, const BindValue &value)
{
    auto lhs = attribute.toNode();
    auto rhs = value.toNode();
    return ComparisonOperator::lessThan(lhs, rhs);
}

ComparisonOperator operator <=(const Attribute &attribute, const BindValue &value)
{
    auto lhs = attribute.toNode();
    auto rhs = value.toNode();
    return ComparisonOperator::lessThanOrEqual(lhs, rhs);
}


} // namespace Ariel
