#include "binarynode.h"

namespace Ariel {

AbstractBinaryNode::AbstractBinaryNode(NodePointer left, NodePointer right)
    : m_left(left),
      m_right(right)
{
}

AbstractBinaryNode::AbstractBinaryNode(const AbstractBinaryNode &other)
{
    copy(m_left, other.m_left);
    copy(m_right, other.m_right);
}

AbstractBinaryNode &AbstractBinaryNode::operator =(AbstractBinaryNode other)
{
    qSwap(m_left, other.m_left);
    qSwap(m_right, other.m_right);
    return *this;
}

void AbstractBinaryNode::setLeft(NodePointer node)
{
    m_left = node;
}

void AbstractBinaryNode::setLeft(AbstractNode *node)
{
    m_left = node;
}

NodePointer AbstractBinaryNode::left() const
{
    return m_left;
}

void AbstractBinaryNode::setRight(NodePointer node)
{
    m_right = node;
}

void AbstractBinaryNode::setRight(AbstractNode *node)
{
    m_right = node;
}

NodePointer AbstractBinaryNode::right() const
{
    return m_right;
}

} // namespace Ariel
