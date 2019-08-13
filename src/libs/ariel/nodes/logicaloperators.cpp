#include "logicaloperators.h"

#include "unarynode.h"

namespace Ariel {

AbstractLogicalOperatorNode::AbstractLogicalOperatorNode(const AbstractLogicalOperatorNode &other)
{
    copy(m_operands, other.m_operands);
}

AbstractLogicalOperatorNode::AbstractLogicalOperatorNode(NodePointer left, NodePointer right)
    : m_operands({ left, right })
{
}

AbstractLogicalOperatorNode &AbstractLogicalOperatorNode::operator =(AbstractLogicalOperatorNode other)
{
    qSwap(m_operands, other.m_operands);
    return *this;
}

QList<NodePointer> AbstractLogicalOperatorNode::operands() const
{
    return m_operands;
}

void AbstractLogicalOperatorNode::addOperand(NodePointer operand)
{
    m_operands.append(operand);
}

} // namespace Ariel
