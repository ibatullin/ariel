#ifndef COMPOUNDOPERATORS_H
#define COMPOUNDOPERATORS_H

#include "binarynode.h"

namespace Ariel {

class AbstractCompoundOperator : public AbstractBinaryNode
{
public:
    using AbstractBinaryNode::AbstractBinaryNode;

    using Pointer = QExplicitlySharedDataPointer<AbstractCompoundOperator>;
};


template<typename T>
class CompoundOperator : public AbstractCompoundOperator,
                         public NodeMethods<T>
{
public:
    using AbstractCompoundOperator::AbstractCompoundOperator;

    void accept(AbstractVisitor &visitor, AbstractCollector &collector) override
    {
        visitor.visit(*static_cast<T *>(this), collector);
    }

    AbstractNode *clone() const override
    {
        return new T(*static_cast<const T *>(this));
    }
};

ARIEL_DECLARE_CRTP(Except, CompoundOperator)
ARIEL_DECLARE_CRTP(Intersect, CompoundOperator)
ARIEL_DECLARE_CRTP(Union, CompoundOperator)
ARIEL_DECLARE_CRTP(UnionAll, CompoundOperator)

} // namespace Ariel

#endif // COMPOUNDOPERATORS_H
