#include "selectstatement.h"

namespace Ariel {

SelectStatement::SelectStatement()
{
    m_context = SelectCore::create();
    m_root = m_context;
}

SelectStatement::SelectStatement(const SelectStatement &other)
{
    copy(m_limit, other.m_limit);
    copy(m_offset, other.m_offset);
    copy(m_orders, other.m_orders);
    copy(m_operator, other.m_operator);
    copy(m_context, other.m_context);

    if (other.m_root == other.m_context)
        m_root = m_context;
    if (other.m_root == other.m_operator)
        m_root = m_operator;
    else
        copy(m_root, other.m_root);
}

SelectStatement &SelectStatement::operator =(SelectStatement other)
{
    qSwap(m_orders, other.m_orders);
    qSwap(m_limit, other.m_limit);
    qSwap(m_offset, other.m_offset);
    qSwap(m_root, other.m_root);
    qSwap(m_operator, other.m_operator);
    qSwap(m_context, other.m_context);
    return *this;
}

void SelectStatement::setOrder(AbstractOrder::Pointer order)
{
    m_orders.clear();
    addOrder(order);
}

void SelectStatement::addOrder(AbstractOrder::Pointer order)
{
    m_orders.append(order);
}

QList<AbstractOrder::Pointer> SelectStatement::orders() const
{
    return m_orders;
}

void SelectStatement::setLimit(Limit::Pointer limit)
{
    m_limit = limit;
}

Limit::Pointer SelectStatement::limit() const
{
    return m_limit;
}

void SelectStatement::setOffset(Offset::Pointer offset)
{
    m_offset = offset;
}

Offset::Pointer SelectStatement::offset() const
{
    return m_offset;
}

void SelectStatement::merge(NodeMethods::Pointer other)
{
    m_orders.append(other->orders());

    if (!m_limit)
        setLimit(other->limit());

    if (!m_offset)
        setOffset(other->offset());
}

NodePointer SelectStatement::root() const
{
    return m_root;
}

SelectCore::Pointer SelectStatement::context() const
{
    return m_context;
}

void SelectStatement::addCore(SelectCore::Pointer core, AbstractCompoundOperator::Pointer compoundOperator)
{
    if (m_operator)
        m_operator->setRight(compoundOperator);
    else
        m_root = compoundOperator;

    m_operator = compoundOperator;
    m_context = core;
}

void SelectStatement::distinctUnion(SelectCore::Pointer core)
{
    addCore<Union>(core);
}

void SelectStatement::unionAll(SelectCore::Pointer core)
{
    addCore<UnionAll>(core);
}

void SelectStatement::intersect(SelectCore::Pointer core)
{
    addCore<Intersect>(core);
}

void SelectStatement::except(SelectCore::Pointer core)
{
    addCore<Except>(core);
}

SelectStatement SelectStatement::distinctUnion(SelectCore::Pointer lhs, SelectCore::Pointer rhs)
{
    return create<Union>(lhs, rhs);
}

SelectStatement SelectStatement::unionAll(SelectCore::Pointer lhs, SelectCore::Pointer rhs)
{
    return create<UnionAll>(lhs, rhs);
}

SelectStatement SelectStatement::intersect(SelectCore::Pointer lhs, SelectCore::Pointer rhs)
{
    return create<Intersect>(lhs, rhs);
}

SelectStatement SelectStatement::except(SelectCore::Pointer lhs, SelectCore::Pointer rhs)
{
    return create<Except>(lhs, rhs);
}

} // namespace Ariel


