#ifndef DELETEMANAGER_H
#define DELETEMANAGER_H

#include "treemanager.h"
#include "nodes/deletestatement.h"

namespace Ariel {

class ComparisonOperator;
class LogicalOperator;

class DeleteManager : public TreeManager<DeleteStatement>
{
public:
    DeleteManager() = default;
    explicit DeleteManager(const Table &table);
    explicit DeleteManager(const TableData::Pointer &table);
    DeleteManager &from(const Table &table);
    DeleteManager &from(const TableNode::Pointer &table);
    DeleteManager &where(const ComparisonOperator &op);
    DeleteManager &where(const LogicalOperator &op);
    DeleteManager &where(const Not::Pointer &op);
    DeleteManager &take(int i);
};

} // namespace Ariel

#endif // DELETEMANAGER_H
