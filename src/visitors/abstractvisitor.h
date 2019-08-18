#ifndef ABSTRACTVISITOR_H
#define ABSTRACTVISITOR_H

#include "../nodes/abstractnode.h"
#include "../collectors/abstractcollector.h"
#include <QVariant>

namespace Ariel {

class AbstractBinaryNode;
class AbstractUnaryNode;
class And;
class Ascending;
class Assignment;
class AttributeNode;
class Between;
class BindValueNode;
class DeleteStatement;
class Descending;
class Equal;
class Except;
class False;
class GreaterThan;
class GreaterThanOrEqual;
class Group;
class Grouping;
class In;
class InsertStatement;
class Intersect;
class Is;
class IsNot;
class JoinSource;
class LessThan;
class LessThanOrEqual;
class Limit;
class LiteralValue;
class Match;
class Not;
class NotBetween;
class NotEqual;
class NotIn;
class NotMatch;
class Null;
class Offset;
class Or;
class SelectCore;
class SelectStatement;
class SqlLiteral;
class Table;
class TableNode;
class True;
class Union;
class UnionAll;
class UnqualifiedColumn;
class UpdateStatement;
class Values;
template<typename T> class List;
using StringList = List<QString>;
using VariantList = List<QVariant>;


namespace Clause {

const char Select[]     = "SELECT";
const char From[]       = " FROM ";
const char OrderBy[]    = " ORDER BY ";
const char Where[]      = " WHERE ";
const char GroupBy[]    = " GROUP BY ";
const char Union[]      = " UNION ";
const char UnionAll[]   = " UNION ALL ";
const char Intersect[]  = " INTERSECT ";
const char Except[]     = " EXCEPT ";
const char InsertInto[] = "INSERT INTO ";
const char Update[]     = "UPDATE ";
const char DeleteFrom[] = "DELETE FROM ";

} // namespace Clause


namespace Delimeters {

const char Space[] = " ";
const char Comma[] = ", ";
const char And[] = " AND ";
const char Or[] = " OR ";

} // namespace Delimeters


class AbstractVisitor
{
public:
    AbstractVisitor() = default;
    virtual ~AbstractVisitor() = default;

    bool visitNode(const NodePointer &node, AbstractCollector &collector);

    virtual void visit(const And &node,                AbstractCollector &collector) = 0;
    virtual void visit(const Ascending &node,          AbstractCollector &collector) = 0;
    virtual void visit(const Assignment &node,         AbstractCollector &collector) = 0;
    virtual void visit(const AttributeNode &node,      AbstractCollector &collector) = 0;
    virtual void visit(const Between &node,            AbstractCollector &collector) = 0;
    virtual void visit(const BindValueNode &node,          AbstractCollector &collector) = 0;
    virtual void visit(const DeleteStatement &node,    AbstractCollector &collector) = 0;
    virtual void visit(const Descending &node,         AbstractCollector &collector) = 0;
    virtual void visit(const Equal &node,              AbstractCollector &collector) = 0;
    virtual void visit(const Except &node,             AbstractCollector &collector) = 0;
    virtual void visit(const False &node,              AbstractCollector &collector) = 0;
    virtual void visit(const GreaterThan &node,        AbstractCollector &collector) = 0;
    virtual void visit(const GreaterThanOrEqual &node, AbstractCollector &collector) = 0;
    virtual void visit(const Group &node,              AbstractCollector &collector) = 0;
    virtual void visit(const Grouping &node,           AbstractCollector &collector) = 0;
    virtual void visit(const In &node,                 AbstractCollector &collector) = 0;
    virtual void visit(const InsertStatement &node,    AbstractCollector &collector) = 0;
    virtual void visit(const Intersect &node,          AbstractCollector &collector) = 0;
    virtual void visit(const Is &node,                 AbstractCollector &collector) = 0;
    virtual void visit(const IsNot &node,              AbstractCollector &collector) = 0;
    virtual void visit(const JoinSource &node,         AbstractCollector &collector) = 0;
    virtual void visit(const LessThan &node,           AbstractCollector &collector) = 0;
    virtual void visit(const LessThanOrEqual &node,    AbstractCollector &collector) = 0;
    virtual void visit(const Limit &node,              AbstractCollector &collector) = 0;
    virtual void visit(const LiteralValue &node,       AbstractCollector &collector) = 0;
    virtual void visit(const Match &node,              AbstractCollector &collector) = 0;
    virtual void visit(const Not &node,                AbstractCollector &collector) = 0;
    virtual void visit(const NotBetween &node,         AbstractCollector &collector) = 0;
    virtual void visit(const NotEqual &node,           AbstractCollector &collector) = 0;
    virtual void visit(const NotIn &node,              AbstractCollector &collector) = 0;
    virtual void visit(const NotMatch &node,           AbstractCollector &collector) = 0;
    virtual void visit(const Null &node,               AbstractCollector &collector) = 0;
    virtual void visit(const Offset &node,             AbstractCollector &collector) = 0;
    virtual void visit(const Or &node,                 AbstractCollector &collector) = 0;
    virtual void visit(const SelectCore &node,         AbstractCollector &collector) = 0;
    virtual void visit(const SelectStatement &node,    AbstractCollector &collector) = 0;
    virtual void visit(const SqlLiteral &node,         AbstractCollector &collector) = 0;
    virtual void visit(const StringList &node,         AbstractCollector &collector) = 0;
    virtual void visit(const TableNode &node,          AbstractCollector &collector) = 0;
    virtual void visit(const True &node,               AbstractCollector &collector) = 0;
    virtual void visit(const Union &node,              AbstractCollector &collector) = 0;
    virtual void visit(const UnionAll &node,           AbstractCollector &collector) = 0;
    virtual void visit(const UnqualifiedColumn &node,  AbstractCollector &collector) = 0;
    virtual void visit(const UpdateStatement &node,    AbstractCollector &collector) = 0;
    virtual void visit(const Values &node,             AbstractCollector &collector) = 0;
    virtual void visit(const VariantList &node,        AbstractCollector &collector) = 0;

    template<typename T>
    void visit(const List<T> &node, AbstractCollector &collector)
    {
        collector << node.list();
    }

protected:
    void maybeVisit(const NodePointer &node, AbstractCollector &collector);

    template<typename T>
    void collect(const QList<QExplicitlySharedDataPointer<T>> &nodes, AbstractCollector &collector,
                 const QString &spacer = QString(' '), const QString &connector = QStringLiteral(", "))
    {
        if (nodes.isEmpty())
            return;

        collector << spacer;
        if (auto first = nodes.first())
            first->accept(*this, collector);

        for (int i = 1; i < nodes.size(); i++) {
            collector << connector;
            if (auto item = nodes.at(i))
                item->accept(*this, collector);
        }
    }

    template<typename T>
    void collect(const QList<T> &nodes, AbstractCollector &collector,
                 const QString &connector = QStringLiteral(", "))
    {
        if (nodes.isEmpty())
            return;

        collector.formatValue(nodes.first());

        for (int i = 1; i < nodes.size(); i++) {
            collector << connector;
            collector.formatValue(nodes.at(i));
        }
    }

    template<typename T>
    inline bool visitNodes(const QList<T> &nodes, AbstractCollector &collector)
    {
        if (nodes.isEmpty())
            return false;

        for (const auto &node : nodes)
            node->accept(*this, collector);

        return true;
    }

    template<typename T>
    typename std::enable_if<std::is_base_of<AbstractBinaryNode, T>::value, void>::type
    visitBinaryNode(const T &node, AbstractCollector &collector, const QString &connector)
    {
        if (node.left() && node.right()) {
            node.left()->accept(*this, collector);
            collector << connector;
            node.right()->accept(*this, collector);
        }
    }

    template<typename T>
    typename std::enable_if<std::is_base_of<AbstractUnaryNode, T>::value, bool>::type
    visitUnaryNode(const T &node, AbstractCollector &collector, const QString &prefix = QString(), const QString &postfix = QString())
    {
        if (const auto expr = node.expression()) {
            collector << prefix;
            expr->accept(*this, collector);
            collector << postfix;
            return true;
        } else {
            return false;
        }
    }
};

} // namespace Ariel

#endif // ABSTRACTVISITOR_H
