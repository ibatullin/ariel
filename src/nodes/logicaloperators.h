#ifndef LOGICALOPERATORS_H
#define LOGICALOPERATORS_H

#include "abstractnode.h"
#include "comparisonoperators.h"
#include "unarynode.h"
#include "../visitors/abstractvisitor.h"

namespace Ariel {

class AbstractLogicalOperatorNode : public AbstractNode
{
public:
    using Pointer = QExplicitlySharedDataPointer<AbstractLogicalOperatorNode>;

    AbstractLogicalOperatorNode() = default;
    AbstractLogicalOperatorNode(const AbstractLogicalOperatorNode &other);
    AbstractLogicalOperatorNode(const NodePointer &left, const NodePointer &right);
    AbstractLogicalOperatorNode &operator =(AbstractLogicalOperatorNode other);
    QList<NodePointer> operands() const;
    void addOperand(const NodePointer &operand);

private:
    QList<NodePointer> m_operands;
};


template<typename T>
class LogicalOperatorNode : public AbstractLogicalOperatorNode,
                            public NodeMethods<T>
{
public:
    using typename NodeMethods<T>::Pointer;
    using AbstractLogicalOperatorNode::AbstractLogicalOperatorNode;

    void accept(AbstractVisitor &visitor, AbstractCollector &collector) override
    {
        visitor.visit(*static_cast<T *>(this), collector);
    }

    AbstractNode *clone() const override
    {
        return new T(*static_cast<const T *>(this));
    }
};

ARIEL_DECLARE_CRTP(And, LogicalOperatorNode)
ARIEL_DECLARE_CRTP(Or, LogicalOperatorNode)

} // namespace Ariel

#endif // LOGICALOPERATORS_H
