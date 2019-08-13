#include "selectcore.h"

namespace Ariel {

SelectCore::SelectCore()
    : m_source(new JoinSource)
{
}

SelectCore::SelectCore(const SelectCore &other)
{
    copy(m_source, other.m_source);
    copy(m_projections, other.m_projections);
    copy(m_wheres, other.m_wheres);
    copy(m_groups, other.m_groups);
}

SelectCore &SelectCore::operator =(SelectCore other)
{
    qSwap(m_source, other.m_source);
    qSwap(m_projections, other.m_projections);
    qSwap(m_wheres, other.m_wheres);
    qSwap(m_groups, other.m_groups);
    return *this;
}

void SelectCore::setSource(JoinSource::Pointer source)
{
    m_source = source;
}

JoinSource::Pointer SelectCore::source() const
{
    return m_source;
}

NodePointer SelectCore::from() const
{
    return m_source->left();
}

void SelectCore::setProjection(AttributeNode::Pointer projection)
{
    m_projections.clear();
    addProjection(projection);
}

void SelectCore::setProjection(SqlLiteral::Pointer literal)
{
    m_projections.clear();
    addProjection(literal);
}

void SelectCore::addProjection(AttributeNode::Pointer projection)
{
    m_projections.append(projection);
}

void SelectCore::addProjection(SqlLiteral::Pointer literal)
{
    m_projections.append(literal);
}

void SelectCore::addProjections(const QList<NodePointer> &projections)
{
    m_projections.append(projections);
}

QList<NodePointer> SelectCore::projections() const
{
    return m_projections;
}

void SelectCore::setWhere(NodePointer where)
{
    m_wheres.clear();
    addWhere(where);
}

void SelectCore::addWhere(NodePointer where)
{
    m_wheres.append(where);
}

void SelectCore::addWheres(const QList<NodePointer> &wheres)
{
    m_wheres.append(wheres);
}

QList<NodePointer> SelectCore::wheres() const
{
    return m_wheres;
}

void SelectCore::setGroup(NodePointer group)
{
    m_groups.clear();
    addGroup(group);
}

void SelectCore::addGroup(NodePointer group)
{
    m_groups.append(group);
}

void SelectCore::addGroups(const QList<NodePointer> &groups)
{
    m_groups.append(groups);
}

QList<NodePointer> SelectCore::groups() const
{
    return m_groups;
}

void SelectCore::clear()
{
    m_source.reset();
    m_projections.clear();
    m_wheres.clear();
    m_groups.clear();
}

} // namespace Ariel