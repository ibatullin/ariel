#include "updatestatement.h"

namespace Ariel {

UpdateStatement::UpdateStatement(const UpdateStatement &other)
{
    copy(m_relation, other.m_relation);
    copy(m_wheres, other.m_wheres);
    copy(m_limit, other.m_limit);
    copy(m_orders, other.m_orders);
    copy(m_values, other.m_values);
}

UpdateStatement &UpdateStatement::operator =(UpdateStatement other)
{
    std::swap(m_relation, other.m_relation);
    std::swap(m_wheres, other.m_wheres);
    std::swap(m_limit, other.m_limit);
    std::swap(m_orders, other.m_orders);
    std::swap(m_values, other.m_values);
    return *this;
}

void UpdateStatement::setRelation(TableNode::Pointer relation)
{
    m_relation = relation;
}

TableNode::Pointer UpdateStatement::relation() const
{
    return m_relation;
}

void UpdateStatement::setWheres(const QList<NodePointer> &wheres)
{
    m_wheres = wheres;
}

void UpdateStatement::addWhere(NodePointer where)
{
    m_wheres.append(where);
}

QList<NodePointer> UpdateStatement::wheres() const
{
    return m_wheres;
}

void UpdateStatement::setOrders(const QList<AbstractOrder::Pointer> &orders)
{
    m_orders = orders;
}

void UpdateStatement::addOrder(AbstractOrder::Pointer order)
{
    m_orders.append(order);
}

QList<AbstractOrder::Pointer> UpdateStatement::orders() const
{
    return m_orders;
}

void UpdateStatement::setLimit(Limit::Pointer limit)
{
    m_limit = limit;
}

Limit::Pointer UpdateStatement::limit() const
{
    return m_limit;
}

void UpdateStatement::setValues(const QList<Assignment::Pointer> &assignments)
{
    m_values = assignments;
}

void UpdateStatement::addValue(Assignment::Pointer assignment)
{
    m_values.append(assignment);
}

void UpdateStatement::addValue(UnqualifiedColumn::Pointer column, const QVariant &value)
{
    addValue(Assignment::create(column, LiteralValue::valueNode(value)));
}

void UpdateStatement::addValue(UnqualifiedColumn::Pointer column, BindValueNode::Pointer value)
{
    addValue(Assignment::create(column, value));
}

QList<Assignment::Pointer> UpdateStatement::values() const
{
    return m_values;
}

} // namespace Ariel
