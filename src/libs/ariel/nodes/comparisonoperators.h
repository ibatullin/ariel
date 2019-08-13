#ifndef COMPARISONOPERATORS_H
#define COMPARISONOPERATORS_H

#include "binarynode.h"
#include "literalvalue.h"

namespace Ariel {

class AbstractComparisonOperatorNode : public AbstractBinaryNode
{
public:
    using AbstractBinaryNode::AbstractBinaryNode;
    using Pointer = QExplicitlySharedDataPointer<AbstractComparisonOperatorNode>;
};


template<typename T>
class ComparisonOperatorNode : public AbstractComparisonOperatorNode,
                               public NodeMethods<T>
{
public:
    using AbstractComparisonOperatorNode::AbstractComparisonOperatorNode;
    using typename NodeMethods<T>::Pointer;

    void accept(AbstractVisitor &visitor, AbstractCollector &collector) override
    {
        visitor.visit(*static_cast<T *>(this), collector);
    }

    AbstractNode *clone() const override
    {
        return new T(*static_cast<const T *>(this));
    }
};


ARIEL_DECLARE_CRTP(Equal, ComparisonOperatorNode)
ARIEL_DECLARE_CRTP(GreaterThan, ComparisonOperatorNode)
ARIEL_DECLARE_CRTP(GreaterThanOrEqual, ComparisonOperatorNode)
ARIEL_DECLARE_CRTP(LessThan, ComparisonOperatorNode)
ARIEL_DECLARE_CRTP(LessThanOrEqual, ComparisonOperatorNode)
ARIEL_DECLARE_CRTP(NotEqual, ComparisonOperatorNode)
ARIEL_DECLARE_CRTP(Between, ComparisonOperatorNode)
ARIEL_DECLARE_CRTP(NotBetween, ComparisonOperatorNode)
ARIEL_DECLARE_CRTP(Match, ComparisonOperatorNode)
ARIEL_DECLARE_CRTP(NotMatch, ComparisonOperatorNode)
ARIEL_DECLARE_CRTP(In, ComparisonOperatorNode)
ARIEL_DECLARE_CRTP(NotIn, ComparisonOperatorNode)



template<typename T>
class IsOperatorNode : public ComparisonOperatorNode<T>
{
public:
    explicit IsOperatorNode(NodePointer attribute)
        : ComparisonOperatorNode<T>(attribute, Null::create())
    {
    }
};


ARIEL_DECLARE_CRTP(Is, IsOperatorNode)
ARIEL_DECLARE_CRTP(IsNot, IsOperatorNode)


} // namespace Ariel

#endif // COMPARISONOPERATORS_H
