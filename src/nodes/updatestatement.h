#ifndef UPDATESTATEMENT_H
#define UPDATESTATEMENT_H

#include "node.h"
#include "tablenode.h"
#include "unarynode.h"
#include "binarynode.h"
#include "order.h"
#include "attributenode.h"
#include "bindvalue.h"

namespace Ariel {

class UpdateStatement : public Node<UpdateStatement>
{
public:
    UpdateStatement() = default;
    UpdateStatement(const UpdateStatement &other);
    UpdateStatement &operator =(UpdateStatement other);
    void setRelation(TableNode::Pointer relation);
    TableNode::Pointer relation() const;
    void setWheres(const QList<NodePointer> &wheres);
    void addWhere(NodePointer where);
    QList<NodePointer> wheres() const;
    void setOrders(const QList<AbstractOrder::Pointer> &orders);
    void addOrder(AbstractOrder::Pointer order);
    QList<AbstractOrder::Pointer> orders() const;
    void setLimit(Limit::Pointer limit);
    Limit::Pointer limit() const;
    void setValues(const QList<Assignment::Pointer> &assignments);
    void addValue(Assignment::Pointer assignment);
    void addValue(UnqualifiedColumn::Pointer column, const QVariant &value);
    void addValue(UnqualifiedColumn::Pointer column, BindValueNode::Pointer value);
    QList<Assignment::Pointer> values() const;

private:
    TableNode::Pointer m_relation;
    QList<NodePointer> m_wheres;
    Limit::Pointer m_limit;
    QList<AbstractOrder::Pointer> m_orders;
    QList<Assignment::Pointer> m_values;
};

} // namespace Ariel

#endif // UPDATESTATEMENT_H
