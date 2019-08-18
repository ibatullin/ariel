#ifndef BINARYNODE_H
#define BINARYNODE_H

#include "abstractnode.h"
#include "../visitors/abstractvisitor.h"

#include <QVariant>

namespace Ariel {

class AbstractBinaryNode : public AbstractNode
{
public:
    AbstractBinaryNode() = default;
    AbstractBinaryNode(NodePointer left, NodePointer right);
    AbstractBinaryNode(const AbstractBinaryNode &other);
    AbstractBinaryNode &operator =(AbstractBinaryNode other);

    void setLeft(NodePointer node);
    void setLeft(AbstractNode *node);
    NodePointer left() const;
    void setRight(NodePointer node);
    void setRight(AbstractNode *node);
    NodePointer right() const;

private:
    NodePointer m_left;
    NodePointer m_right;
};


template<typename T>
class BinaryNode : public AbstractBinaryNode,
                   public NodeMethods<T>
{
public:
    using AbstractBinaryNode::AbstractBinaryNode;

    void accept(AbstractVisitor &visitor, AbstractCollector &collector) override
    {
        visitor.visit(*static_cast<T *>(this), collector);
    }

    AbstractNode *clone() const override
    {
        return new T(*static_cast<const T *>(this));
    }
};


ARIEL_DECLARE_CRTP(Assignment, BinaryNode)
// TODO: As, Join

} // namespace Ariel

#endif // BINARYNODE_H
