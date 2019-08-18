#include "insertstatement.h"

namespace Ariel {

InsertStatement::InsertStatement(const InsertStatement &other)
{
    copy(m_relation, other.m_relation);
    copy(m_columns, other.m_columns);
    copy(m_values, other.m_values);
    copy(m_select, other.m_select);
}

InsertStatement &InsertStatement::operator =(InsertStatement other)
{
    std::swap(m_relation, other.m_relation);
    std::swap(m_columns, other.m_columns);
    std::swap(m_values, other.m_values);
    std::swap(m_select, other.m_select);
    return *this;
}

void InsertStatement::setRelation(const TableNode::Pointer &relation)
{
    m_relation = relation;
}

TableNode::Pointer InsertStatement::relation() const
{
    return m_relation;
}

void InsertStatement::setColumns(const QList<UnqualifiedColumn::Pointer> columns)
{
    m_columns = columns;
}

void InsertStatement::addColumn(const UnqualifiedColumn::Pointer &column)
{
    m_columns.append(column);
}

QList<UnqualifiedColumn::Pointer> InsertStatement::columns() const
{
    return m_columns;
}

void InsertStatement::setValues(const QList<NodePointer> &values)
{
    m_values = values;
}

void InsertStatement::addValue(const QVariant &value)
{
    addValue(LiteralValue::valueNode(value));
}

void InsertStatement::addValue(const NodePointer &value)
{
    m_values.append(value);
}

void InsertStatement::addValue(const UnqualifiedColumn::Pointer &column, const QVariant &value)
{
    addColumn(column);
    addValue(value);
}

void InsertStatement::addValue(const UnqualifiedColumn::Pointer &column, const BindValueNode::Pointer &value)
{
    addColumn(column);
    addValue(value);
}

QList<NodePointer> InsertStatement::values() const
{
    return m_values;
}

void InsertStatement::setSelect(const SelectStatement::Pointer &select)
{
    m_select = select;
}

SelectStatement::Pointer InsertStatement::select() const
{
    return m_select;
}

} // namespace Ariel
