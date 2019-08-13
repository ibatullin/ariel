#include "insertmanager.h"

#include "bindvalue.h"
#include "table.h"

namespace Ariel {

InsertManager::InsertManager()
{
}

InsertManager::InsertManager(TableData::Pointer table)
    : TreeManager(InsertStatement::create())
{
    into(TableNode::create(table));
}

InsertManager::InsertManager(const Table &table)
    : TreeManager(InsertStatement::create())
{
    into(table);
}

InsertManager &InsertManager::into(const Table &table)
{
    return into(table.toNode());
}

InsertManager &InsertManager::into(TableNode::Pointer table)
{
    ast()->setRelation(table);
    return *this;
}

InsertManager &InsertManager::insert(const Attribute &attribute, const QVariant &value)
{
    checkRelation(attribute);
    ast()->addValue(attribute.toUnqualifiedColumn(), value);
    return *this;
}

InsertManager &InsertManager::insert(const Attribute &attribute, const BindValue &value)
{
    checkRelation(attribute);
    ast()->addValue(attribute.toUnqualifiedColumn(), value.toNode());
    return *this;
}

InsertManager &InsertManager::column(const Attribute &attribute)
{
    ast()->addColumn(attribute.toUnqualifiedColumn());
    return *this;
}

QList<UnqualifiedColumn::Pointer> InsertManager::columns() const
{
    return ast()->columns();
}

void InsertManager::setValues(const QList<NodePointer> &values)
{
    ast()->setValues(values);
}

QList<NodePointer> InsertManager::values() const
{
    return ast()->values();
}

InsertManager InsertManager::select(SelectStatement::Pointer select)
{
    ast()->setSelect(select);
    return *this;
}

InsertManager InsertManager::select(const SelectManager &selectManager)
{
    return select(selectManager.ast());
}

void InsertManager::checkRelation(const Attribute &attribute)
{
    if (!ast()->relation())
        ast()->setRelation(attribute.relation().toNode());
    else
        Q_ASSERT(*attribute.relation().data() == *ast()->relation()->data());
}

} // namespace Ariel
