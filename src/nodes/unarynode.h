#ifndef UNARYNODE_H
#define UNARYNODE_H

#include "abstractnode.h"
#include "node.h"
#include "literalvalue.h"

#include <QVariant>

namespace Ariel {

class AbstractUnaryNode : public AbstractNode
{
public:
    AbstractUnaryNode() = default;
    explicit AbstractUnaryNode(NodePointer expression);
    AbstractUnaryNode(const AbstractUnaryNode &other);
    AbstractUnaryNode &operator =(AbstractUnaryNode other);

    void setExpression(NodePointer expression);
    NodePointer expression() const;

protected:
    NodePointer m_expression;
};



template<typename T>
class UnaryNode : public AbstractUnaryNode,
                  public NodeMethods<T>
{
public:
    using AbstractUnaryNode::AbstractUnaryNode;

    void accept(AbstractVisitor &visitor, AbstractCollector &collector) override
    {
        visitor.visit(*static_cast<T *>(this), collector);
    }

    AbstractNode *clone() const override
    {
        return new T(*static_cast<const T *>(this));
    }
};


ARIEL_DECLARE_CRTP(Limit, UnaryNode)
ARIEL_DECLARE_CRTP(Offset, UnaryNode)
ARIEL_DECLARE_CRTP(Group, UnaryNode)
ARIEL_DECLARE_CRTP(Lock, UnaryNode)
ARIEL_DECLARE_CRTP(Not, UnaryNode)
ARIEL_DECLARE_CRTP(On, UnaryNode)
ARIEL_DECLARE_CRTP(Top, UnaryNode)
ARIEL_DECLARE_CRTP(Grouping, UnaryNode)
ARIEL_DECLARE_CRTP(Values, UnaryNode)

} // namespace Ariel

//ARIEL_DECLARE_SHARED_POINTER_CLONE_FUNC(AbstractUnaryNode)

#endif // UNARYNODE_H
