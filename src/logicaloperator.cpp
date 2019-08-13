#include "logicaloperator.h"
#include "comparisonoperator_p.h"

namespace Ariel {

LogicalOperator::LogicalOperator(And::Pointer node)
    : m_node(node)
{
}

LogicalOperator::LogicalOperator(Or::Pointer node)
    : m_node(node)
{
}

LogicalOperator::LogicalOperator(Not::Pointer node)
    : m_node(node)
{
}

NodePointer LogicalOperator::toNode() const
{
    return m_node;
}

Grouping::Pointer LogicalOperator::toGroupingNode() const
{
    return Grouping::create(m_node);
}

LogicalOperator LogicalOperator::andOperator(NodePointer lhs, NodePointer rhs)
{
    return LogicalOperator(And::create(lhs, rhs));
}

LogicalOperator LogicalOperator::orOperator(NodePointer lhs, NodePointer rhs)
{
    return LogicalOperator(Or::create(lhs, rhs));
}

LogicalOperator LogicalOperator::notOperator(NodePointer node)
{
    return LogicalOperator(Not::create(node));
}


// And

LogicalOperator operator &&(const ComparisonOperator &lhs, const ComparisonOperator &rhs)
{
    return LogicalOperator::andOperator(lhs.toNode(), rhs.toNode());
}

LogicalOperator operator &&(const LogicalOperator &lhs, const ComparisonOperator &rhs)
{
    return LogicalOperator::andOperator(lhs.toNode(), rhs.toNode());
}

LogicalOperator operator &&(const ComparisonOperator &lhs, const LogicalOperator &rhs)
{
    return LogicalOperator::andOperator(lhs.toNode(), rhs.toGroupingNode());
}

LogicalOperator operator &&(const LogicalOperator &lhs, const LogicalOperator &rhs)
{
    return LogicalOperator::andOperator(lhs.toGroupingNode(), rhs.toGroupingNode());
}


// Or

LogicalOperator operator ||(const ComparisonOperator &lhs, const ComparisonOperator &rhs)
{
    return LogicalOperator::orOperator(lhs.toNode(), rhs.toNode());
}

LogicalOperator operator ||(const LogicalOperator &lhs, const ComparisonOperator &rhs)
{
    return LogicalOperator::orOperator(lhs.toNode(), rhs.toNode());
}

LogicalOperator operator ||(const ComparisonOperator &lhs, const LogicalOperator &rhs)
{
    return LogicalOperator::orOperator(lhs.toNode(), rhs.toGroupingNode());
}

LogicalOperator operator ||(const LogicalOperator &lhs, const LogicalOperator &rhs)
{
    return LogicalOperator::orOperator(lhs.toGroupingNode(), rhs.toGroupingNode());
}


// Not

LogicalOperator operator !(const LogicalOperator &op)
{
    return LogicalOperator::notOperator(op.toGroupingNode());
}

LogicalOperator operator !(const ComparisonOperator &op)
{
    return LogicalOperator::notOperator(op.toNode());
}

SpecialComparisonOperator operator !(const SpecialComparisonOperator &op)
{
    const auto holder = op.holder();
    const auto node = op.toNode();
    Q_ASSERT(holder);
    Q_ASSERT(node);
    auto opposite = holder->createOppositeOperator(node->left(), node->right());
    return SpecialComparisonOperator(opposite, holder->oppositeHolder());
}


} // namespace Ariel
