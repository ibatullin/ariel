#include "updatemanager.h"

#include "table.h"
#include "comparisonoperator.h"
#include "logicaloperator.h"

namespace Ariel {

UpdateManager::UpdateManager(TableNode::Pointer table)
{
    this->table(table);
}

UpdateManager::UpdateManager(const Table &table)
{
    this->table(table);
}

UpdateManager::UpdateManager(TableData::Pointer table)
{
    this->table(TableNode::create(table));
}

UpdateManager &UpdateManager::table(const Table &table)
{
    return this->table(table.toNode());
}

UpdateManager &UpdateManager::table(TableNode::Pointer table)
{
    ast()->setRelation(table);
    return *this;
}

UpdateManager &UpdateManager::where(const ComparisonOperator &op)
{
    ast()->addWhere(op.toNode());
    return *this;
}

UpdateManager &UpdateManager::where(const LogicalOperator &op)
{
    ast()->addWhere(op.toNode());
    return *this;
}

UpdateManager &UpdateManager::where(Not::Pointer op)
{
    ast()->addWhere(op);
    return *this;
}

UpdateManager &UpdateManager::order(AbstractOrder::Pointer order)
{
    ast()->addOrder(order);
    return *this;
}

UpdateManager &UpdateManager::update(const Attribute &attribute, const QVariant &value)
{
    ast()->addValue(attribute.toUnqualifiedColumn(), value);
    return *this;
}

UpdateManager &UpdateManager::update(const Attribute &attribute, const BindValue &value)
{
    ast()->addValue(attribute.toUnqualifiedColumn(), value.toNode());
    return *this;
}

UpdateManager &UpdateManager::take(int i)
{
    const auto value = LiteralValue::create(i);
    const auto limit = Limit::create(value);
    ast()->setLimit(limit);
    return *this;
}

} // namespace Ariel
