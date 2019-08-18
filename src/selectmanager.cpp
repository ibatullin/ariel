#include "selectmanager.h"

#include "nodes/literalvalue.h"
#include "table.h"
#include "comparisonoperator.h"
#include "logicaloperator.h"

namespace Ariel {

SelectManager::SelectManager(const Table &table)
{
    from(table);
}

SelectManager::SelectManager(const TableData::Pointer &table)
{
    from(table);
}

SelectManager &SelectManager::from(const Table &table)
{
    return from(table.data());
}

SelectManager &SelectManager::from(const TableData::Pointer &table)
{
    m_table = table;
    context()->source()->setLeft(TableNode::create(table));
    return *this;
}

void SelectManager::setProjection(const Attribute &projection)
{
    context()->setProjection(projection.toNode());
}

void SelectManager::setOrder(const AbstractOrder::Pointer &order)
{
    ast()->setOrder(order);
}

void SelectManager::setWhere(const ComparisonOperator &op)
{
    context()->setWhere(op.toNode());
}

void SelectManager::setWhere(const LogicalOperator &op)
{
    context()->setWhere(op.toNode());
}

void SelectManager::setWhere(const Not::Pointer &op)
{
    context()->setWhere(op);
}

void SelectManager::setLimit(const Limit::Pointer &limit)
{
    // TODO: add TOP
    ast()->setLimit(limit);
}

Limit::Pointer SelectManager::limit() const
{
    return ast()->limit();
}

void SelectManager::setOffset(const Offset::Pointer &offset)
{
    ast()->setOffset(offset);
}

Offset::Pointer SelectManager::offset() const
{
    return ast()->offset();
}

SelectManager &SelectManager::select(const Attribute &projection)
{
    context()->addProjection(projection.toNode());
    return *this;
}

SelectManager &SelectManager::select(const QList<Attribute> &projections)
{
    for (const auto &attribute : projections)
        context()->addProjection(attribute.toNode());

    return *this;
}

SelectManager &SelectManager::select(std::initializer_list<Attribute> projections)
{
    for (const auto &attribute : projections)
        context()->addProjection(attribute.toNode());

    return *this;
}

SelectManager &SelectManager::select(const QString &projection)
{
    Attribute attribute(projection, m_table);
    return select(attribute);
}

SelectManager &SelectManager::select(const QStringList &projections)
{
    for (const auto &projection : projections) {
        Attribute attribute(projection, m_table);
        context()->addProjection(attribute.toNode());
    }

    return *this;
}

SelectManager &SelectManager::select(std::initializer_list<const char *> projections)
{
    for (const auto &projection : projections) {
        Attribute attribute(projection, m_table);
        context()->addProjection(attribute.toNode());
    }

    return *this;
}

SelectManager &SelectManager::select(const SqlLiteral::Pointer &sqlLiteral)
{
    context()->addProjection(sqlLiteral);
    return *this;
}

SelectManager &SelectManager::order(const AbstractOrder::Pointer &order)
{
    ast()->addOrder(order);
    return *this;
}

SelectManager &SelectManager::where(const Attribute &attribute)
{
    return where(attribute == true);
}

SelectManager &SelectManager::where(const ComparisonOperator &op)
{
    context()->addWhere(op.toNode());
    return *this;
}

SelectManager &SelectManager::where(const LogicalOperator &op)
{
    context()->addWhere(op.toNode());
    return *this;
}

SelectManager &SelectManager::group(const Attribute &attribute)
{
    auto group = Group::create(attribute.toNode());
    context()->addGroup(group);
    return *this;
}

SelectManager &SelectManager::group(const QList<Attribute> &attributes)
{
    for (const auto &attribute : attributes) {
        auto group = Group::create(attribute.toNode());
        context()->addGroup(group);
    }

    return *this;
}

SelectManager &SelectManager::group(std::initializer_list<Attribute> attributes)
{
    for (const auto &attribute : attributes) {
        auto group = Group::create(attribute.toNode());
        context()->addGroup(group);
    }

    return *this;
}

SelectManager &SelectManager::group(const QString &attribute)
{
    return group(Attribute(attribute, m_table));
}

SelectManager &SelectManager::group(const QStringList &attributes)
{
    for (const auto &name : attributes) {
        Attribute attribute(name, m_table);
        auto group = Group::create(attribute.toNode());
        context()->addGroup(group);
    }

    return *this;
}

SelectManager &SelectManager::group(std::initializer_list<const char *> attributes)
{
    for (const auto &name : attributes) {
        Attribute attribute(name, m_table);
        auto group = Group::create(attribute.toNode());
        context()->addGroup(group);
    }

    return *this;
}

SelectManager &SelectManager::take(int limit)
{
    auto value = LiteralValue::create(limit);
    return take(Limit::create(value));
}

SelectManager &SelectManager::take(const Limit::Pointer &limit)
{
    ast()->setLimit(limit);
    return *this;
}

SelectManager &SelectManager::skip(int offset)
{
    auto value = LiteralValue::create(offset);
    return skip(Offset::create(value));
}

SelectManager &SelectManager::skip(const Offset::Pointer &offset)
{
    ast()->setOffset(offset);
    return *this;
}

SelectManager &SelectManager::distinctUnion(const SelectCore::Pointer &core)
{
    ast()->distinctUnion(core);
    return *this;
}

SelectManager &SelectManager::unionAll(const SelectCore::Pointer &core)
{
    ast()->unionAll(core);
    return *this;
}

SelectManager &SelectManager::intersect(const SelectCore::Pointer &core)
{
    ast()->intersect(core);
    return *this;
}

SelectManager &SelectManager::except(const SelectCore::Pointer &core)
{
    ast()->except(core);
    return *this;
}

SelectManager &SelectManager::distinctUnion(const SelectManager &other)
{
    ast()->merge(other.ast());
    return distinctUnion(other.context());
}

SelectManager &SelectManager::unionAll(const SelectManager &other)
{
    ast()->merge(other.ast());
    return unionAll(other.context());
}

SelectManager &SelectManager::intersect(const SelectManager &other)
{
    ast()->merge(other.ast());
    return intersect(other.context());
}

SelectManager &SelectManager::except(const SelectManager &other)
{
    ast()->merge(other.ast());
    return except(other.context());
}

SelectManager SelectManager::distinctUnion(SelectManager lhs, const SelectManager &rhs)
{
    lhs.detach();
    return lhs.distinctUnion(rhs);
}

SelectManager SelectManager::unionAll(SelectManager lhs, const SelectManager &rhs)
{
    SelectManager manager(lhs);
    manager.detach();
    return manager.unionAll(rhs);
}

SelectManager SelectManager::intersect(SelectManager lhs, const SelectManager &rhs)
{
    lhs.detach();
    return lhs.intersect(rhs);
}

SelectManager SelectManager::except(SelectManager lhs, const SelectManager &rhs)
{
    lhs.detach();
    return lhs.except(rhs);
}

SelectCore::Pointer SelectManager::context() const
{
    Q_ASSERT(ast()->context());
    return ast()->context();
}

} // namespace Ariel
