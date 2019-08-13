#include "order.h"

namespace Ariel {

AbstractOrder::Direction AbstractOrder::direction() const
{
    return m_direction;
}

AbstractOrder::AbstractOrder(AbstractOrder::Direction direction)
    : m_direction(direction)
{
}

AbstractOrder::AbstractOrder(NodePointer expression, AbstractOrder::Direction direction)
    : AbstractUnaryNode(expression),
      m_direction(direction)
{
}


Ascending::Ascending()
    : Order(AbstractOrder::Direction::Ascending)
{
}

Ascending::Ascending(NodePointer expression)
    : Order(expression, AbstractOrder::Direction::Ascending)
{
}


Descending::Descending()
    : Order(AbstractOrder::Direction::Descending)
{
}

Descending::Descending(NodePointer expression)
    : Order(expression, AbstractOrder::Direction::Descending)
{
}

} // namespace Ariel
