#ifndef ORDER_H
#define ORDER_H

#include "unarynode.h"

namespace Ariel {

class AbstractOrder : public AbstractUnaryNode
{
public:
    enum class Direction {
        Ascending,
        Descending
    };

    using Pointer = QExplicitlySharedDataPointer<AbstractOrder>;

    Direction direction() const;

protected:
    AbstractOrder() = default;
    explicit AbstractOrder(Direction direction);
    AbstractOrder(const NodePointer &expression, Direction direction);

private:
    Direction m_direction = Direction::Ascending;
};



template<typename T>
class Order : public AbstractOrder
{
public:
    void accept(AbstractVisitor &visitor, AbstractCollector &collector) override
    {
        visitor.visit(*static_cast<T *>(this), collector);
    }

    AbstractNode *clone() const override
    {
        return new T(*static_cast<const T *>(this));
    }

protected:
    using AbstractOrder::AbstractOrder;
};



class Ascending : public Order<Ascending>,
                  public NodeMethods<Ascending>
{
public:
    using NodeMethods::Pointer;
    Ascending();
    explicit Ascending(const NodePointer &expression);
};



class Descending : public Order<Descending>,
                   public NodeMethods<Descending>
{
public:
    using NodeMethods::Pointer;
    Descending();
    explicit Descending(const NodePointer &expression);
};

} // namespace Ariel

#endif // ORDER_H
