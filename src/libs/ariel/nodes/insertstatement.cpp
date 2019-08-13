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
    qSwap(m_relation, other.m_relation);
    qSwap(m_columns, other.m_columns);
    qSwap(m_values, other.m_values);
    qSwap(m_select, other.m_select);
    return *this;
}

void InsertStatement::setRelation(TableNode::Pointer relation)
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

void InsertStatement::addColumn(UnqualifiedColumn::Pointer column)
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

void InsertStatement::addValue(NodePointer value)
{
    m_values.append(value);
}

void InsertStatement::addValue(UnqualifiedColumn::Pointer column, const QVariant &value)
{
    addColumn(column);
    addValue(value);
}

void InsertStatement::addValue(UnqualifiedColumn::Pointer column, BindValueNode::Pointer value)
{
    addColumn(column);
    addValue(value);
}

QList<NodePointer> InsertStatement::values() const
{
    return m_values;
}

void InsertStatement::setSelect(SelectStatement::Pointer select)
{
    m_select = select;
}

SelectStatement::Pointer InsertStatement::select() const
{
    return m_select;
}

} // namespace Ariel
