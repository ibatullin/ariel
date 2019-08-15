#ifndef INSERTMANAGER_H
#define INSERTMANAGER_H

#include "treemanager.h"
#include "nodes/insertstatement.h"

namespace Ariel {

class Attribute;
class BindValue;
class SelectManager;

class InsertManager : public TreeManager<InsertStatement>
{
public:
    InsertManager() = default;
    explicit InsertManager(TableData::Pointer table);
    explicit InsertManager(const Table &table);

    InsertManager &into(const Table &table);
    InsertManager &into(TableNode::Pointer table);
    InsertManager &insert(const Attribute &attribute, const QVariant &value);
    InsertManager &insert(const Attribute &attribute, const BindValue &value);
    InsertManager &column(const Attribute &attribute);
    QList<UnqualifiedColumn::Pointer> columns() const;
    void setValues(const QList<NodePointer> &values);
    QList<NodePointer> values() const;
    InsertManager select(SelectStatement::Pointer select);
    InsertManager select(const SelectManager &selectManager);

private:
    void checkRelation(const Attribute &attribute);
};

} // namespace Ariel

#endif // INSERTMANAGER_H
