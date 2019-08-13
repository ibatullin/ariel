#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "nodes/attributenode.h"
#include "nodes/order.h"
#include "comparisonoperator.h"
#include "logicaloperator.h"

namespace Ariel {

class BindValue;
class Table;

class Attribute
{
public:
    Attribute(const QString &name, TableData::Pointer relation);
    explicit Attribute(AttributeData::Pointer d);
    void setName(const QString &name);
    QString name() const;
    Table relation() const;
    Ascending::Pointer ascending() const;
    Descending::Pointer descending() const;
    SpecialComparisonOperator between(const QVariant &value1, const QVariant &value2) const;
    SpecialComparisonOperator match(const QString &pattern) const;
    SpecialComparisonOperator in(const QVariant &value) const;
    SpecialComparisonOperator notIn(const QVariant &value) const;
    SpecialComparisonOperator isNull() const;
    SpecialComparisonOperator isNotNull() const;
    AttributeNode::Pointer toNode() const;
    UnqualifiedColumn::Pointer toUnqualifiedColumn() const;

private:
    AttributeData::Pointer d;
};

ComparisonOperator operator ==(const Attribute &attribute, const QVariant &value);
ComparisonOperator operator ==(const Attribute &attribute, const BindValue &value);
ComparisonOperator operator ==(const Attribute &attribute, const QStringList &list);
ComparisonOperator operator ==(const Attribute &attribute, const QVariantList &list);

ComparisonOperator operator !=(const Attribute &attribute, const QVariant &value);
ComparisonOperator operator !=(const Attribute &attribute, const BindValue &value);
ComparisonOperator operator !=(const Attribute &attribute, const QStringList &list);
ComparisonOperator operator !=(const Attribute &attribute, const QVariantList &list);

ComparisonOperator operator >(const Attribute &attribute, const QVariant &value);
ComparisonOperator operator >(const Attribute &attribute, const BindValue &value);

ComparisonOperator operator >=(const Attribute &attribute, const QVariant &value);
ComparisonOperator operator >=(const Attribute &attribute, const BindValue &value);

ComparisonOperator operator <(const Attribute &attribute, const QVariant &value);
ComparisonOperator operator <(const Attribute &attribute, const BindValue &value);

ComparisonOperator operator <=(const Attribute &attribute, const QVariant &value);
ComparisonOperator operator <=(const Attribute &attribute, const BindValue &value);

ComparisonOperator operator ==(const Attribute &lhs, const Attribute &rhs);
ComparisonOperator operator !=(const Attribute &lhs, const Attribute &rhs);
ComparisonOperator operator >(const Attribute &lhs, const Attribute &rhs);
ComparisonOperator operator >=(const Attribute &lhs, const Attribute &rhs);
ComparisonOperator operator <(const Attribute &lhs, const Attribute &rhs);
ComparisonOperator operator <=(const Attribute &lhs, const Attribute &rhs);

ComparisonOperator operator !(const Attribute &attribute);

} // namespace Ariel

#endif // ATTRIBUTE_H
