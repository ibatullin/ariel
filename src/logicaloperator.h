#ifndef LOGICALOPERATOR_H
#define LOGICALOPERATOR_H

#include "nodes/logicaloperators.h"
#include "comparisonoperator.h"

namespace Ariel {

class LogicalOperator
{
public:
    explicit LogicalOperator(And::Pointer node);
    explicit LogicalOperator(Or::Pointer node);
    explicit LogicalOperator(Not::Pointer node);
    NodePointer toNode() const;
    Grouping::Pointer toGroupingNode() const;
    static LogicalOperator andOperator(NodePointer lhs, NodePointer rhs);
    static LogicalOperator orOperator(NodePointer lhs, NodePointer rhs);
    static LogicalOperator notOperator(NodePointer node);

private:
    NodePointer m_node;
};


LogicalOperator operator &&(const ComparisonOperator &lhs, const ComparisonOperator &rhs);
LogicalOperator operator &&(const LogicalOperator &lhs, const ComparisonOperator &rhs);
LogicalOperator operator &&(const ComparisonOperator &lhs, const LogicalOperator &rhs);
LogicalOperator operator &&(const LogicalOperator &lhs, const LogicalOperator &rhs);

LogicalOperator operator ||(const ComparisonOperator &lhs, const ComparisonOperator &rhs);
LogicalOperator operator ||(const LogicalOperator &lhs, const ComparisonOperator &rhs);
LogicalOperator operator ||(const ComparisonOperator &lhs, const LogicalOperator &rhs);
LogicalOperator operator ||(const LogicalOperator &lhs, const LogicalOperator &rhs);

LogicalOperator operator !(const LogicalOperator &op);
LogicalOperator operator !(const ComparisonOperator &op);
SpecialComparisonOperator operator !(const SpecialComparisonOperator &op);

} // namespace Ariel

#endif // LOGICALOPERATOR_H
