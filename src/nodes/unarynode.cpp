#include "unarynode.h"

namespace Ariel {

AbstractUnaryNode::AbstractUnaryNode(const NodePointer &expression)
    : m_expression(expression)
{
}

AbstractUnaryNode::AbstractUnaryNode(const AbstractUnaryNode &other)
{
    copy(m_expression, other.m_expression);
}

AbstractUnaryNode &AbstractUnaryNode::operator =(AbstractUnaryNode other)
{
    std::swap(m_expression, other.m_expression);
    return *this;
}

void AbstractUnaryNode::setExpression(const NodePointer &expression)
{
    m_expression = expression;
}

NodePointer AbstractUnaryNode::expression() const
{
    return m_expression;
}

} // namespace Ariel
