#include "deletemanager.h"

#include "comparisonoperator.h"
#include "logicaloperator.h"
#include "table.h"

namespace Ariel {

DeleteManager::DeleteManager(const Table &table)
    : TreeManager<DeleteStatement>(DeleteStatement::create())
{
    from(table);
}

DeleteManager::DeleteManager(const TableData::Pointer &table)
    : TreeManager<DeleteStatement>(DeleteStatement::create())
{
    from(TableNode::create(table));
}

DeleteManager &DeleteManager::from(const Table &table)
{
    ast()->setRelation(table.toNode());
    return *this;
}

DeleteManager &DeleteManager::from(const TableNode::Pointer &table)
{
    ast()->setRelation(table);
    return *this;
}

DeleteManager &DeleteManager::where(const ComparisonOperator &op)
{
    ast()->addWhere(op.toNode());
    return *this;
}

DeleteManager &DeleteManager::where(const LogicalOperator &op)
{
    ast()->addWhere(op.toNode());
    return *this;
}

DeleteManager &DeleteManager::where(const Not::Pointer &op)
{
    ast()->addWhere(op);
    return *this;
}

DeleteManager &DeleteManager::take(int i)
{
    const auto value = LiteralValue::create(i);
    const auto limit = Limit::create(value);
    ast()->setLimit(limit);
    return *this;
}

} // namespace Ariel

