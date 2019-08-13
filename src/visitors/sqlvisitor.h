#ifndef SQLVISITOR_H
#define SQLVISITOR_H

#include "abstractvisitor.h"
#include "../nodes/attributenode.h"
#include "../nodes/order.h"
#include "../nodes/comparisonoperators.h"

#include <QSqlDriver>
#include <QPointer>

namespace Ariel {

class SqlVisitor : public AbstractVisitor
{
public:
    SqlVisitor() = default;

private:
    void visit(const And &node,                AbstractCollector &collector) override;
    void visit(const Ascending &node,          AbstractCollector &collector) override;
    void visit(const Assignment &node,         AbstractCollector &collector) override;
    void visit(const AttributeNode &node,      AbstractCollector &collector) override;
    void visit(const Between &node,            AbstractCollector &collector) override;
    void visit(const BindValueNode &node,      AbstractCollector &collector) override;
    void visit(const DeleteStatement &node,    AbstractCollector &collector) override;
    void visit(const Descending &node,         AbstractCollector &collector) override;
    void visit(const Equal &node,              AbstractCollector &collector) override;
    void visit(const Except &node,             AbstractCollector &collector) override;
    void visit(const False &node,              AbstractCollector &collector) override;
    void visit(const GreaterThan &node,        AbstractCollector &collector) override;
    void visit(const GreaterThanOrEqual &node, AbstractCollector &collector) override;
    void visit(const Group &node,              AbstractCollector &collector) override;
    void visit(const Grouping &node,           AbstractCollector &collector) override;
    void visit(const In &node,                 AbstractCollector &collector) override;
    void visit(const InsertStatement &node,    AbstractCollector &collector) override;
    void visit(const Intersect &node,          AbstractCollector &collector) override;
    void visit(const Is &node,                 AbstractCollector &collector) override;
    void visit(const IsNot &node,              AbstractCollector &collector) override;
    void visit(const JoinSource &node,         AbstractCollector &collector) override;
    void visit(const LessThan &node,           AbstractCollector &collector) override;
    void visit(const LessThanOrEqual &node,    AbstractCollector &collector) override;
    void visit(const Limit &node,              AbstractCollector &collector) override;
    void visit(const LiteralValue &node,       AbstractCollector &collector) override;
    void visit(const Match &node,              AbstractCollector &collector) override;
    void visit(const Not &node,                AbstractCollector &collector) override;
    void visit(const NotBetween &node,         AbstractCollector &collector) override;
    void visit(const NotEqual &node,           AbstractCollector &collector) override;
    void visit(const NotIn &node,              AbstractCollector &collector) override;
    void visit(const NotMatch &node,           AbstractCollector &collector) override;
    void visit(const Null &node,               AbstractCollector &collector) override;
    void visit(const Offset &node,             AbstractCollector &collector) override;
    void visit(const Or &node,                 AbstractCollector &collector) override;
    void visit(const SelectCore &node,         AbstractCollector &collector) override;
    void visit(const SelectStatement &node,    AbstractCollector &collector) override;
    void visit(const SqlLiteral &node,         AbstractCollector &collector) override;
    void visit(const StringList &node,         AbstractCollector &collector) override;
    void visit(const TableNode &node,          AbstractCollector &collector) override;
    void visit(const True &node,               AbstractCollector &collector) override;
    void visit(const Union &node,              AbstractCollector &collector) override;
    void visit(const UnionAll &node,           AbstractCollector &collector) override;
    void visit(const UnqualifiedColumn &node,  AbstractCollector &collector) override;
    void visit(const UpdateStatement &node,    AbstractCollector &collector) override;
    void visit(const Values &node,             AbstractCollector &collector) override;
    void visit(const VariantList &node,        AbstractCollector &collector) override;
};

} // namespace Ariel

template<typename T>
typename std::enable_if<std::is_base_of<Ariel::AbstractNode, T>::value, QDebug>::type
operator<<(QDebug debug, const T &node)
{
    Ariel::SqlVisitor visitor;
    Ariel::StringCollector collector;
    visitor.visit(node, collector);
    debug << collector.value();
    return debug;
}

template<typename T>
typename std::enable_if<std::is_base_of<Ariel::AbstractNode, T>::value, QDebug>::type
operator<<(QDebug debug, QExplicitlySharedDataPointer<T> node)
{
    Ariel::SqlVisitor visitor;
    Ariel::StringCollector collector;
    visitor.visitNode(node, collector);
    debug << collector.value();
    return debug;
}

#endif // SQLVISITOR_H
