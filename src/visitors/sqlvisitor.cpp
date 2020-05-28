#include "sqlvisitor.h"

#include "../table.h"
#include "../nodes/selectcore.h"
#include "../nodes/binarynode.h"
#include "../nodes/unarynode.h"
#include "../nodes/order.h"
#include "../nodes/insertstatement.h"
#include "../nodes/updatestatement.h"
#include "../nodes/deletestatement.h"
#include "../nodes/literalvalue.h"

#include <QSqlField>
#include <QSqlDatabase>

namespace Ariel {

void SqlVisitor::visit(const And &node, AbstractCollector &collector)
{
    collect(node.operands(), collector, QString(), Delimeters::And);
}

void SqlVisitor::visit(const Ascending &node, AbstractCollector &collector)
{
    visitNode(node.expression(), collector);
    collector << QStringLiteral(" ASC");
}

void SqlVisitor::visit(const Assignment &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, QStringLiteral(" = "));
}

void SqlVisitor::visit(const AttributeNode &node, AbstractCollector &collector)
{
    if (node.name() == Ariel::Star) {
        collector.escapeIdentifier(node.relation());
        collector.collect("." + node.name());
    } else {
        const QString identifier = node.relation() + "." + node.name();
        collector.escapeIdentifier(identifier);
    }
}

void SqlVisitor::visit(const Between &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, QStringLiteral(" BETWEEN "));
}

void SqlVisitor::visit(const BindValueNode &node, AbstractCollector &collector)
{
    collector.bindValue(node.value());
}

void SqlVisitor::visit(const DeleteStatement &node, AbstractCollector &collector)
{
    collector << Clause::DeleteFrom;
    visitNode(node.relation(), collector);
    collect(node.wheres(), collector, Clause::Where);
    if (auto limit = node.limit()) {
        collector << Delimeters::Space;
        visitNode(limit, collector);
    }
}

void SqlVisitor::visit(const Descending &node, AbstractCollector &collector)
{
    visitNode(node.expression(), collector);
    collector << QStringLiteral(" DESC");
}

void SqlVisitor::visit(const Equal &node, AbstractCollector &collector)
{
    visitNode(node.left(), collector);
    if (const auto right = node.right()) {
        collector << QStringLiteral(" = ");
        visitNode(right, collector);
    } else {
        collector << QStringLiteral(" IS NULL");
    }
}

void SqlVisitor::visit(const Except &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, Clause::Except);
}

void SqlVisitor::visit(const False &, AbstractCollector &collector)
{
    collector << QStringLiteral("FALSE");
}

void SqlVisitor::visit(const GreaterThan &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, QStringLiteral(" > "));
}

void SqlVisitor::visit(const GreaterThanOrEqual &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, QStringLiteral(" >= "));
}

void SqlVisitor::visit(const Group &node, AbstractCollector &collector)
{
    visitUnaryNode(node, collector);
}

void SqlVisitor::visit(const Grouping &node, AbstractCollector &collector)
{
    visitUnaryNode(node, collector, QStringLiteral("("), QStringLiteral(")"));
}

void SqlVisitor::visit(const In &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, QStringLiteral(" IN ("));
    collector << QStringLiteral(")");
}

void SqlVisitor::visit(const InsertStatement &node, AbstractCollector &collector)
{
    collector << Clause::InsertInto;
    visitNode(node.relation(), collector);
    collector << QStringLiteral(" (");
    collect(node.columns(), collector, QString());
    collector << QStringLiteral(") ");

    if (!node.values().isEmpty()) {
        collect(node.values(), collector, QStringLiteral("VALUES ("), Delimeters::Comma);
        collector << QStringLiteral(")");
    } else {
        visitNode(node.select(), collector);
    }
}

void SqlVisitor::visit(const Intersect &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, Clause::Intersect);
}

void SqlVisitor::visit(const Is &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, QStringLiteral(" IS "));
}

void SqlVisitor::visit(const IsNot &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, QStringLiteral(" IS NOT "));
}

void SqlVisitor::visit(const JoinSource &node, AbstractCollector &collector)
{
    if (auto left = node.left())
        visitNode(left, collector);

    if (auto right = node.right()) {
        if (node.left())
            collector << Delimeters::Space;
        // TODO: inject join
        visitNode(right, collector);
    }
}

void SqlVisitor::visit(const LessThan &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, QStringLiteral(" < "));
}

void SqlVisitor::visit(const LessThanOrEqual &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, QStringLiteral(" <= "));
}

void SqlVisitor::visit(const Limit &node, AbstractCollector &collector)
{
    visitUnaryNode(node, collector, QStringLiteral("LIMIT "));
}

void SqlVisitor::visit(const LiteralValue &node, AbstractCollector &collector)
{
    collector.formatValue(node.value());
}

void SqlVisitor::visit(const Match &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, QStringLiteral(" LIKE "));
}

void SqlVisitor::visit(const Max &node, AbstractCollector &collector)
{
    collector << QStringLiteral("MAX(");
    visitUnaryNode(node, collector);
    collector << QStringLiteral(")");
}

void SqlVisitor::visit(const Min &node, AbstractCollector &collector)
{

}

void SqlVisitor::visit(const Not &node, AbstractCollector &collector)
{
    visitUnaryNode(node, collector, QStringLiteral("NOT "));
}

void SqlVisitor::visit(const NotBetween &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, QStringLiteral(" NOT BETWEEN "));
}

void SqlVisitor::visit(const NotEqual &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, QStringLiteral(" <> "));
}

void SqlVisitor::visit(const NotIn &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, QStringLiteral(" NOT IN ("));
    collector << QStringLiteral(")");
}

void SqlVisitor::visit(const NotMatch &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, QStringLiteral(" NOT LIKE "));
}

void SqlVisitor::visit(const Null &, AbstractCollector &collector)
{
    collector << QStringLiteral("NULL");
}

void SqlVisitor::visit(const Offset &node, AbstractCollector &collector)
{
    visitUnaryNode(node, collector, QStringLiteral("OFFSET "));
}

void SqlVisitor::visit(const Or &node, AbstractCollector &collector)
{
    collect(node.operands(), collector, QString(), Delimeters::Or);
}

void SqlVisitor::visit(const SelectCore &node, AbstractCollector &collector)
{
    collector << Clause::Select;

    // TODO: TOP
    // TODO: SET

    collect(node.projections(), collector);

    if (auto source = node.source()) {
        collector << Clause::From;
        visitNode(source, collector);
    }

    collect(node.wheres(), collector, Clause::Where, Delimeters::And);
    collect(node.groups(), collector, Clause::GroupBy, Delimeters::Comma);

    // TODO: having
    // TODO: window
}

void SqlVisitor::visit(const SelectStatement &node, AbstractCollector &collector)
{
    visitNode(node.root(), collector);

    collect(node.orders(), collector, Clause::OrderBy, Delimeters::Comma);
    maybeVisit(node.limit(), collector);
    maybeVisit(node.offset(), collector);
}

void SqlVisitor::visit(const SqlLiteral &node, AbstractCollector &collector)
{
    collector << node.value().toString();
}

void SqlVisitor::visit(const StringList &node, AbstractCollector &collector)
{
    collect(node.list(), collector);
}

void SqlVisitor::visit(const TableNode &node, AbstractCollector &collector)
{
    collector.collect(node.name());
}

void SqlVisitor::visit(const True &, AbstractCollector &collector)
{
    collector << QStringLiteral("TRUE");
}

void SqlVisitor::visit(const Union &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, Clause::Union);
}

void SqlVisitor::visit(const UnionAll &node, AbstractCollector &collector)
{
    visitBinaryNode(node, collector, Clause::UnionAll);
}

void SqlVisitor::visit(const UnqualifiedColumn &node, AbstractCollector &collector)
{
    if (node.name() == Ariel::Star) {
        collector.collect(node.name());
    } else {
        const QString identifier = node.name();
        collector.escapeIdentifier(identifier);
    }
}

void SqlVisitor::visit(const UpdateStatement &node, AbstractCollector &collector)
{
    collector << Clause::Update;
    visitNode(node.relation(), collector);
    collector << QStringLiteral(" SET");
    collect(node.values(), collector);
    collect(node.wheres(), collector, Clause::Where);
    collect(node.orders(), collector, Clause::OrderBy);
    if (const auto limit = node.limit()) {
        collector << Delimeters::Space;
        visitNode(limit, collector);
    }
}

void SqlVisitor::visit(const Values &node, AbstractCollector &collector)
{
    visitUnaryNode(node, collector, QStringLiteral("VALUES ("), QStringLiteral(")"));
}

void SqlVisitor::visit(const VariantList &node, AbstractCollector &collector)
{
    collect(node.list(), collector);
}

} // namespace Ariel

