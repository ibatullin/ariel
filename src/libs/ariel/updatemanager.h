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
    explicit UpdateManager(TableNode::Pointer table);
    explicit UpdateManager(TableData::Pointer table);
    UpdateManager &table(const Table &table);
    UpdateManager &table(TableNode::Pointer table);
    UpdateManager &where(const ComparisonOperator &op);
    UpdateManager &where(const LogicalOperator &op);
    UpdateManager &where(Not::Pointer op);
    UpdateManager &order(AbstractOrder::Pointer order);
    UpdateManager &set(const Attribute &attribute, const QVariant &value);
    UpdateManager &set(const Attribute &attribute, const BindValue &value);
    UpdateManager &take(int i);
};


} // namespace Ariel

#endif // UPDATEMANAGER_H
