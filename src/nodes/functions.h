#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "unarynode.h"

namespace Ariel {


class AbstractFunction : public AbstractUnaryNode
{
public:
    using AbstractUnaryNode::AbstractUnaryNode;
    using Pointer = QExplicitlySharedDataPointer<AbstractFunction>;
};

template<typename T>
class BaseFunction : public UnaryNode<T>
{
public:
    using UnaryNode<T>::UnaryNode;
    void accept(AbstractVisitor &visitor, AbstractCollector &collector) override
    {
        visitor.visit(*static_cast<T *>(this), collector);
    }

    AbstractNode *clone() const override
    {
        return new T(*static_cast<const T *>(this));
    }
};

ARIEL_DECLARE_CRTP(Count, BaseFunction)
ARIEL_DECLARE_CRTP(Sum, BaseFunction)
ARIEL_DECLARE_CRTP(Max, BaseFunction)
ARIEL_DECLARE_CRTP(Min, BaseFunction)
ARIEL_DECLARE_CRTP(Avg, BaseFunction)
ARIEL_DECLARE_CRTP(Extract, BaseFunction)

} // namespace Ariel

#endif // FUNCTIONS_H
