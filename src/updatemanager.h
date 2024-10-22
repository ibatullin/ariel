#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include "treemanager.h"
#include "bindvalue.h"
#include "nodes/updatestatement.h"

namespace Ariel {

class Attribute;
class ComparisonOperator;
class LogicalOperator;

class UpdateManager : public TreeManager<UpdateStatement>
{
public:
    UpdateManager() = default;
    explicit UpdateManager(const Table &table);
    explicit UpdateManager(const TableNode::Pointer &table);
    explicit UpdateManager(const TableData::Pointer &table);
    UpdateManager &table(const Table &table);
    UpdateManager &table(const TableNode::Pointer &table);
    UpdateManager &where(const ComparisonOperator &op);
    UpdateManager &where(const LogicalOperator &op);
    UpdateManager &where(const Not::Pointer &op);
    UpdateManager &order(const AbstractOrder::Pointer &order);
    UpdateManager &update(const Attribute &attribute, const QVariant &value);
    UpdateManager &update(const Attribute &attribute, const BindValue &value);
    UpdateManager &take(int i);
};


} // namespace Ariel

#endif // UPDATEMANAGER_H
