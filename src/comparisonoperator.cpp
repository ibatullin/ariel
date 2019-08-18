#include "comparisonoperator.h"
#include "comparisonoperator_p.h"

namespace Ariel {

ComparisonOperator::ComparisonOperator(const AbstractComparisonOperatorNode::Pointer &node)
    : m_node(node)
{
}

ComparisonOperator::ComparisonOperator(const AbstractComparisonOperatorNode::Pointer &node,
                                       const QSharedPointer<BaseOperatorHolder> &holder)
    : m_node(node),
      m_holder(holder)
{
}

AbstractComparisonOperatorNode::Pointer ComparisonOperator::toNode() const
{
    return m_node;
}

ComparisonOperator ComparisonOperator::equal(const NodePointer &lhs, const NodePointer &rhs)
{
    return ComparisonOperator(Equal::create(lhs, rhs));
}

ComparisonOperator ComparisonOperator::notEqual(const NodePointer &lhs, const NodePointer &rhs)
{
    return ComparisonOperator(NotEqual::create(lhs, rhs));
}

ComparisonOperator ComparisonOperator::lessThan(const NodePointer &lhs, const NodePointer &rhs)
{
    return ComparisonOperator(LessThan::create(lhs, rhs));
}

ComparisonOperator ComparisonOperator::lessThanOrEqual(const NodePointer &lhs, const NodePointer &rhs)
{
    return ComparisonOperator(LessThanOrEqual::create(lhs, rhs));
}

ComparisonOperator ComparisonOperator::greaterThan(const NodePointer &lhs, const NodePointer &rhs)
{
    return ComparisonOperator(GreaterThan::create(lhs, rhs));
}

ComparisonOperator ComparisonOperator::greaterThanOrEqual(const NodePointer &lhs, const NodePointer &rhs)
{
    return ComparisonOperator(GreaterThanOrEqual::create(lhs, rhs));
}

QSharedPointer<BaseOperatorHolder> ComparisonOperator::holder() const
{
    return m_holder;
}



SpecialComparisonOperator SpecialComparisonOperator::between(const AttributeNode::Pointer &attribute,
                                                             const NodePointer &lhs, const NodePointer &rhs)
{
    auto holder = OperatorHolder<Between, NotBetween>::create();
    return SpecialComparisonOperator(Between::create(attribute, And::create(lhs, rhs)), holder);
}

SpecialComparisonOperator SpecialComparisonOperator::matches(const AttributeNode::Pointer &attribute,
                                                             const NodePointer &expression)
{
    auto holder = OperatorHolder<Match, NotMatch>::create();
    return SpecialComparisonOperator(Match::create(attribute, expression), holder);
}

SpecialComparisonOperator SpecialComparisonOperator::in(const AttributeNode::Pointer &attribute,
                                                        const NodePointer &expression)
{
    auto holder = OperatorHolder<In, NotIn>::create();
    return SpecialComparisonOperator(In::create(attribute, expression), holder);
}

SpecialComparisonOperator SpecialComparisonOperator::notIn(const AttributeNode::Pointer &attribute,
                                                           const NodePointer &expression)
{
    auto holder = OperatorHolder<NotIn, In>::create();
    return SpecialComparisonOperator(NotIn::create(attribute, expression), holder);
}

SpecialComparisonOperator SpecialComparisonOperator::isNull(const AttributeNode::Pointer &attribute)
{
    auto holder = OperatorHolder<Is, IsNot>::create();
    return SpecialComparisonOperator(Is::create(attribute), holder);
}

SpecialComparisonOperator SpecialComparisonOperator::isNotNull(const AttributeNode::Pointer &attribute)
{
    auto holder = OperatorHolder<IsNot, Is>::create();
    return SpecialComparisonOperator(IsNot::create(attribute), holder);
}



template<>
AbstractComparisonOperatorNode::Pointer
OperatorHolder<Is, IsNot>::createDirectOperator(const NodePointer &left, const NodePointer &right) const
{
    Q_UNUSED(right)
    return Is::create(left);
}

template<>
AbstractComparisonOperatorNode::Pointer
OperatorHolder<Is, IsNot>::createOppositeOperator(const NodePointer &left, const NodePointer &right) const
{
    Q_UNUSED(right)
    return IsNot::create(left);
}

template<>
AbstractComparisonOperatorNode::Pointer
OperatorHolder<IsNot, Is>::createDirectOperator(const NodePointer &left, const NodePointer &right) const
{
    Q_UNUSED(right)
    return IsNot::create(left);
}

template<>
AbstractComparisonOperatorNode::Pointer
OperatorHolder<IsNot, Is>::createOppositeOperator(const NodePointer &left, const NodePointer &right) const
{
    Q_UNUSED(right)
    return Is::create(left);
}


SpecialComparisonOperator::SpecialComparisonOperator(const AbstractComparisonOperatorNode::Pointer &node,
                                                     const QSharedPointer<BaseOperatorHolder> &holder)
    : ComparisonOperator(node, holder)
{
}


} // namespace Ariel
