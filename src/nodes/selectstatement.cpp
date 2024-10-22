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
    std::swap(m_orders, other.m_orders);
    std::swap(m_limit, other.m_limit);
    std::swap(m_offset, other.m_offset);
    std::swap(m_root, other.m_root);
    std::swap(m_operator, other.m_operator);
    std::swap(m_context, other.m_context);
    return *this;
}

void SelectStatement::setOrder(const AbstractOrder::Pointer &order)
{
    m_orders.clear();
    addOrder(order);
}

void SelectStatement::addOrder(const AbstractOrder::Pointer &order)
{
    m_orders.append(order);
}

QList<AbstractOrder::Pointer> SelectStatement::orders() const
{
    return m_orders;
}

void SelectStatement::setLimit(const Limit::Pointer &limit)
{
    m_limit = limit;
}

Limit::Pointer SelectStatement::limit() const
{
    return m_limit;
}

void SelectStatement::setOffset(const Offset::Pointer &offset)
{
    m_offset = offset;
}

Offset::Pointer SelectStatement::offset() const
{
    return m_offset;
}

void SelectStatement::merge(const SelectStatement::Pointer &other)
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

void SelectStatement::addCore(const SelectCore::Pointer &core,
                              const AbstractCompoundOperator::Pointer &compoundOperator)
{
    if (m_operator)
        m_operator->setRight(compoundOperator);
    else
        m_root = compoundOperator;

    m_operator = compoundOperator;
    m_context = core;
}

void SelectStatement::distinctUnion(const SelectCore::Pointer &core)
{
    addCore<Union>(core);
}

void SelectStatement::unionAll(const SelectCore::Pointer &core)
{
    addCore<UnionAll>(core);
}

void SelectStatement::intersect(const SelectCore::Pointer &core)
{
    addCore<Intersect>(core);
}

void SelectStatement::except(const SelectCore::Pointer &core)
{
    addCore<Except>(core);
}

SelectStatement SelectStatement::distinctUnion(const SelectCore::Pointer &lhs,
                                               const SelectCore::Pointer &rhs)
{
    return create<Union>(lhs, rhs);
}

SelectStatement SelectStatement::unionAll(const SelectCore::Pointer &lhs,
                                          const SelectCore::Pointer &rhs)
{
    return create<UnionAll>(lhs, rhs);
}

SelectStatement SelectStatement::intersect(const SelectCore::Pointer &lhs,
                                           const SelectCore::Pointer &rhs)
{
    return create<Intersect>(lhs, rhs);
}

SelectStatement SelectStatement::except(const SelectCore::Pointer &lhs,
                                        const SelectCore::Pointer &rhs)
{
    return create<Except>(lhs, rhs);
}

} // namespace Ariel


