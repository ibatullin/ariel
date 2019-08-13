#ifndef DELETESTATEMENT_H
#define DELETESTATEMENT_H

#include "node.h"
#include "tablenode.h"
#include "unarynode.h"

namespace Ariel {

class DeleteStatement : public Node<DeleteStatement>
{
public:
    DeleteStatement() = default;
    DeleteStatement(const DeleteStatement &other);
    DeleteStatement &operator =(DeleteStatement other);
    void setRelation(TableNode::Pointer relation);
    TableNode::Pointer relation() const;
    void setWheres(const QList<NodePointer> &wheres);
    void addWhere(NodePointer where);
    QList<NodePointer> wheres() const;
    void setLimit(Limit::Pointer limit);
    Limit::Pointer limit() const;

private:
    TableNode::Pointer m_relation;
    QList<NodePointer> m_wheres;
    Limit::Pointer m_limit;
};

} // namespace Ariel

#endif // DELETESTATEMENT_H
