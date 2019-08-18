#ifndef COMPARISONOPERATOR_H
#define COMPARISONOPERATOR_H

#include "nodes/comparisonoperators.h"
#include "nodes/logicaloperators.h"
#include "nodes/attributenode.h"
#include "nodes/literalvalue.h"

#include <QSharedPointer>

namespace Ariel {

class BaseOperatorHolder;

class ComparisonOperator
{
public:
    explicit ComparisonOperator(const AbstractComparisonOperatorNode::Pointer &node);
    ComparisonOperator(const AbstractComparisonOperatorNode::Pointer &node,
                       const QSharedPointer<BaseOperatorHolder> &holder);
    AbstractComparisonOperatorNode::Pointer toNode() const;
    static ComparisonOperator equal(const NodePointer &lhs, const NodePointer &rhs);
    static ComparisonOperator notEqual(const NodePointer &lhs, const NodePointer &rhs);
    static ComparisonOperator lessThan(const NodePointer &lhs, const NodePointer &rhs);
    static ComparisonOperator lessThanOrEqual(const NodePointer &lhs, const NodePointer &rhs);
    static ComparisonOperator greaterThan(const NodePointer &lhs, const NodePointer &rhs);
    static ComparisonOperator greaterThanOrEqual(const NodePointer &lhs, const NodePointer &rhs);

protected:
    QSharedPointer<BaseOperatorHolder> holder() const;

private:
    AbstractComparisonOperatorNode::Pointer m_node;
    QSharedPointer<BaseOperatorHolder> m_holder;
};


class SpecialComparisonOperator : public ComparisonOperator
{
public:
    explicit SpecialComparisonOperator(const AbstractComparisonOperatorNode::Pointer &node,
                                       const QSharedPointer<BaseOperatorHolder> &holder);

    static SpecialComparisonOperator between(const AttributeNode::Pointer &attribute,
                                             const NodePointer &lhs, const NodePointer &rhs);
    static SpecialComparisonOperator matches(const AttributeNode::Pointer &attribute,
                                             const NodePointer &expression);
    static SpecialComparisonOperator in(const AttributeNode::Pointer &attribute,
                                        const NodePointer &expression);
    static SpecialComparisonOperator notIn(const AttributeNode::Pointer &attribute,
                                           const NodePointer &expression);
    static SpecialComparisonOperator isNull(const AttributeNode::Pointer &attribute);
    static SpecialComparisonOperator isNotNull(const AttributeNode::Pointer &attribute);

    friend SpecialComparisonOperator operator !(const SpecialComparisonOperator &op);
};

} // namespace Ariel

#endif // COMPARISONOPERATOR_H
