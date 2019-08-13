#include "comparisonoperator.h"
#include "comparisonoperator_p.h"

namespace Ariel {

ComparisonOperator::ComparisonOperator(AbstractComparisonOperatorNode::Pointer node)
    : m_node(node)
{
}

ComparisonOperator::ComparisonOperator(AbstractComparisonOperatorNode::Pointer node, QSharedPointer<BaseOperatorHolder> holder)
    : m_node(node),
      m_holder(holder)
{
}

AbstractComparisonOperatorNode::Pointer ComparisonOperator::toNode() const
{
    return m_node;
}

ComparisonOperator ComparisonOperator::equal(NodePointer lhs, NodePointer rhs)
{
    return ComparisonOperator(Equal::create(lhs, rhs));
}

ComparisonOperator ComparisonOperator::notEqual(NodePointer lhs, NodePointer rhs)
{
    return ComparisonOperator(NotEqual::create(lhs, rhs));
}

ComparisonOperator ComparisonOperator::lessThan(NodePointer lhs, NodePointer rhs)
{
    return ComparisonOperator(LessThan::create(lhs, rhs));
}

ComparisonOperator ComparisonOperator::lessThanOrEqual(NodePointer lhs, NodePointer rhs)
{
    return ComparisonOperator(LessThanOrEqual::create(lhs, rhs));
}

ComparisonOperator ComparisonOperator::greaterThan(NodePointer lhs, NodePointer rhs)
{
    return ComparisonOperator(GreaterThan::create(lhs, rhs));
}

ComparisonOperator ComparisonOperator::greaterThanOrEqual(NodePointer lhs, NodePointer rhs)
{
    return ComparisonOperator(GreaterThanOrEqual::create(lhs, rhs));
}

QSharedPointer<BaseOperatorHolder> ComparisonOperator::holder() const
{
    return m_holder;
}



SpecialComparisonOperator SpecialComparisonOperator::between(AttributeNode::Pointer attribute, NodePointer lhs, NodePointer rhs)
{
    auto holder = OperatorHolder<Between, NotBetween>::create();
    return SpecialComparisonOperator(Between::create(attribute, And::create(lhs, rhs)), holder);
}

SpecialComparisonOperator SpecialComparisonOperator::matches(AttributeNode::Pointer attribute, NodePointer expression)
{
    auto holder = OperatorHolder<Match, NotMatch>::create();
    return SpecialComparisonOperator(Match::create(attribute, expression), holder);
}

SpecialComparisonOperator SpecialComparisonOperator::in(AttributeNode::Pointer attribute, NodePointer expression)
{
    auto holder = OperatorHolder<In, NotIn>::create();
    return SpecialComparisonOperator(In::create(attribute, expression), holder);
}

SpecialComparisonOperator SpecialComparisonOperator::notIn(AttributeNode::Pointer attribute, NodePointer expression)
{
    auto holder = OperatorHolder<NotIn, In>::create();
    return SpecialComparisonOperator(NotIn::create(attribute, expression), holder);
}

SpecialComparisonOperator SpecialComparisonOperator::isNull(AttributeNode::Pointer attribute)
{
    auto holder = OperatorHolder<Is, IsNot>::create();
    return SpecialComparisonOperator(Is::create(attribute), holder);
}

SpecialComparisonOperator SpecialComparisonOperator::isNotNull(AttributeNode::Pointer attribute)
{
    auto holder = OperatorHolder<IsNot, Is>::create();
    return SpecialComparisonOperator(IsNot::create(attribute), holder);
}



template<>
AbstractComparisonOperatorNode::Pointer
OperatorHolder<Is, IsNot>::createDirectOperator(NodePointer left, NodePointer right) const
{
    Q_UNUSED(right)
    return Is::create(left);
}

template<>
AbstractComparisonOperatorNode::Pointer
OperatorHolder<Is, IsNot>::createOppositeOperator(NodePointer left, NodePointer right) const
{
    Q_UNUSED(right)
    return IsNot::create(left);
}

template<>
AbstractComparisonOperatorNode::Pointer
OperatorHolder<IsNot, Is>::createDirectOperator(NodePointer left, NodePointer right) const
{
    Q_UNUSED(right)
    return IsNot::create(left);
}

template<>
AbstractComparisonOperatorNode::Pointer
OperatorHolder<IsNot, Is>::createOppositeOperator(NodePointer left, NodePointer right) const
{
    Q_UNUSED(right)
    return Is::create(left);
}


SpecialComparisonOperator::SpecialComparisonOperator(AbstractComparisonOperatorNode::Pointer node, QSharedPointer<BaseOperatorHolder> holder)
    : ComparisonOperator(node, holder)
{
}


} // namespace Ariel
