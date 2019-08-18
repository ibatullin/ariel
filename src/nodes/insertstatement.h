#ifndef INSERTSTATEMENT_H
#define INSERTSTATEMENT_H

#include "node.h"
#include "tablenode.h"
#include "attributenode.h"
#include "literalvalue.h"
#include "selectstatement.h"
#include "bindvalue.h"

namespace Ariel {

class InsertStatement : public Node<InsertStatement>
{
public:
    InsertStatement() = default;
    InsertStatement(const InsertStatement &other);
    InsertStatement &operator =(InsertStatement other);
    void setRelation(const TableNode::Pointer &relation);
    TableNode::Pointer relation() const;
    void setColumns(const QList<UnqualifiedColumn::Pointer> columns);
    void addColumn(const UnqualifiedColumn::Pointer &column);
    QList<UnqualifiedColumn::Pointer> columns() const;
    void setValues(const QList<NodePointer> &values);
    void addValue(const QVariant &value);
    void addValue(const NodePointer &value);
    void addValue(const UnqualifiedColumn::Pointer &column, const QVariant &value);
    void addValue(const UnqualifiedColumn::Pointer &column, const BindValueNode::Pointer &value);
    QList<NodePointer> values() const;
    void setSelect(const SelectStatement::Pointer &select);
    SelectStatement::Pointer select() const;

private:
    TableNode::Pointer m_relation;
    QList<UnqualifiedColumn::Pointer> m_columns;
    QList<NodePointer> m_values;
    SelectStatement::Pointer m_select;
};

} // namespace Ariel

#endif // INSERTSTATEMENT_H
