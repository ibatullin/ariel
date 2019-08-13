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
    explicit ComparisonOperator(AbstractComparisonOperatorNode::Pointer node);
    ComparisonOperator(AbstractComparisonOperatorNode::Pointer node,
                       QSharedPointer<BaseOperatorHolder> holder);
    AbstractComparisonOperatorNode::Pointer toNode() const;
    static ComparisonOperator equal(NodePointer lhs, NodePointer rhs);
    static ComparisonOperator notEqual(NodePointer lhs, NodePointer rhs);
    static ComparisonOperator lessThan(NodePointer lhs, NodePointer rhs);
    static ComparisonOperator lessThanOrEqual(NodePointer lhs, NodePointer rhs);
    static ComparisonOperator greaterThan(NodePointer lhs, NodePointer rhs);
    static ComparisonOperator greaterThanOrEqual(NodePointer lhs, NodePointer rhs);

protected:
    QSharedPointer<BaseOperatorHolder> holder() const;

private:
    AbstractComparisonOperatorNode::Pointer m_node;
    QSharedPointer<BaseOperatorHolder> m_holder;
};


class SpecialComparisonOperator : public ComparisonOperator
{
public:
    explicit SpecialComparisonOperator(AbstractComparisonOperatorNode::Pointer node,
                                       QSharedPointer<BaseOperatorHolder> holder);

    static SpecialComparisonOperator between(AttributeNode::Pointer attribute,
                                             NodePointer lhs, NodePointer rhs);
    static SpecialComparisonOperator matches(AttributeNode::Pointer attribute, NodePointer expression);
    static SpecialComparisonOperator in(AttributeNode::Pointer attribute, NodePointer expression);
    static SpecialComparisonOperator notIn(AttributeNode::Pointer attribute, NodePointer expression);
    static SpecialComparisonOperator isNull(AttributeNode::Pointer attribute);
    static SpecialComparisonOperator isNotNull(AttributeNode::Pointer attribute);

    friend SpecialComparisonOperator operator !(const SpecialComparisonOperator &op);
};

} // namespace Ariel

#endif // COMPARISONOPERATOR_H
