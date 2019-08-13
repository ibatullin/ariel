#ifndef SELECTCORE_H
#define SELECTCORE_H

#include "node.h"
#include "binarynode.h"
#include "comparisonoperators.h"
#include "logicaloperators.h"
#include "attributenode.h"

namespace Ariel {

class JoinSource : public BinaryNode<JoinSource>
{
public:
    using BinaryNode<JoinSource>::BinaryNode;
};


class SelectCore : public Node<SelectCore>
{
public:
    SelectCore();
    SelectCore(const SelectCore &other);
    SelectCore &operator =(SelectCore other);
    void setSource(JoinSource::Pointer source);
    JoinSource::Pointer source() const;
    NodePointer from() const;
    void setProjection(AttributeNode::Pointer projection);
    void setProjection(SqlLiteral::Pointer literal);
    void addProjection(AttributeNode::Pointer projection);
    void addProjection(SqlLiteral::Pointer literal);
    void addProjections(const QList<NodePointer> &projections);
    QList<NodePointer> projections() const;
    void setWhere(NodePointer where);
    void addWhere(NodePointer where);
    void addWheres(const QList<NodePointer> &wheres);
    QList<NodePointer> wheres() const;
    void setGroup(NodePointer group);
    void addGroup(NodePointer group);
    void addGroups(const QList<NodePointer> &groups);
    QList<NodePointer> groups() const;

    void clear();

private:
    JoinSource::Pointer m_source;
    QList<NodePointer> m_projections;
    QList<NodePointer> m_wheres;
    QList<NodePointer> m_groups;
    // havings
    // windows
};

} // namespace Ariel

#endif // SELECTCORE_H
