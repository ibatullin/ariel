#include "logicaloperators.h"

#include "unarynode.h"

namespace Ariel {

AbstractLogicalOperatorNode::AbstractLogicalOperatorNode(const AbstractLogicalOperatorNode &other)
{
    copy(m_operands, other.m_operands);
}

AbstractLogicalOperatorNode::AbstractLogicalOperatorNode(const NodePointer &left, const NodePointer &right)
    : m_operands({ left, right })
{
}

AbstractLogicalOperatorNode &AbstractLogicalOperatorNode::operator =(AbstractLogicalOperatorNode other)
{
    std::swap(m_operands, other.m_operands);
    return *this;
}

QList<NodePointer> AbstractLogicalOperatorNode::operands() const
{
    return m_operands;
}

void AbstractLogicalOperatorNode::addOperand(const NodePointer &operand)
{
    m_operands.append(operand);
}

} // namespace Ariel
