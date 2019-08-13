#ifndef COMPARISONOPERATOR_P_H
#define COMPARISONOPERATOR_P_H

#include "comparisonoperator.h"

#include <QSharedPointer>

namespace Ariel {

class AbstractComparisonOperatorNode;

class BaseOperatorHolder
{
public:
    virtual ~BaseOperatorHolder() = default;
    virtual AbstractComparisonOperatorNode::Pointer createDirectOperator(NodePointer left, NodePointer right) const = 0;
    virtual AbstractComparisonOperatorNode::Pointer createOppositeOperator(NodePointer left, NodePointer right) const = 0;
    virtual QSharedPointer<BaseOperatorHolder> oppositeHolder() const = 0;
};


template<typename Op1, typename Op2>
class OperatorHolder : public BaseOperatorHolder
{
public:
    AbstractComparisonOperatorNode::Pointer createDirectOperator(NodePointer left, NodePointer right) const override
    {
        return Op1::create(left, right);
    }

    AbstractComparisonOperatorNode::Pointer createOppositeOperator(NodePointer left, NodePointer right) const override
    {
        return Op2::create(left, right);
    }

    QSharedPointer<BaseOperatorHolder> oppositeHolder() const override
    {
        return create<Op2, Op1>();
    }

    template<typename T, typename U>
    static QSharedPointer<BaseOperatorHolder> create()
    {
        return QSharedPointer<OperatorHolder<T, U>>::create();
    }

    static QSharedPointer<BaseOperatorHolder> create()
    {
        return create<Op1, Op2>();
    }
};

template<>
AbstractComparisonOperatorNode::Pointer
OperatorHolder<Is, IsNot>::createDirectOperator(NodePointer left, NodePointer) const;

template<>
AbstractComparisonOperatorNode::Pointer
OperatorHolder<Is, IsNot>::createOppositeOperator(NodePointer left, NodePointer) const;

template<>
AbstractComparisonOperatorNode::Pointer
OperatorHolder<IsNot, Is>::createDirectOperator(NodePointer left, NodePointer) const;

template<>
AbstractComparisonOperatorNode::Pointer
OperatorHolder<IsNot, Is>::createOppositeOperator(NodePointer left, NodePointer) const;

} // namespace Ariel

#endif // COMPARISONOPERATOR_P_H
