#include "deletestatement.h"

namespace Ariel {

DeleteStatement::DeleteStatement(const DeleteStatement &other)
{
    copy(m_relation, other.m_relation);
    copy(m_wheres, other.m_wheres);
    copy(m_limit, other.m_limit);
}

DeleteStatement &DeleteStatement::operator =(DeleteStatement other)
{
    qSwap(m_relation, other.m_relation);
    qSwap(m_wheres, other.m_wheres);
    qSwap(m_limit, other.m_limit);
    return *this;
}

void DeleteStatement::setRelation(TableNode::Pointer relation)
{
    m_relation = relation;
}

TableNode::Pointer DeleteStatement::relation() const
{
    return m_relation;
}

void DeleteStatement::setWheres(const QList<NodePointer> &wheres)
{
    m_wheres = wheres;
}

void DeleteStatement::addWhere(NodePointer where)
{
    m_wheres.append(where);
}

QList<NodePointer> DeleteStatement::wheres() const
{
    return m_wheres;
}

void DeleteStatement::setLimit(Limit::Pointer limit)
{
    m_limit = limit;
}

Limit::Pointer DeleteStatement::limit() const
{
    return m_limit;
}

} // namespace Ariel

