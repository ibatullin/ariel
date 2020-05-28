#include "table.h"
#include "table_p.h"

namespace Ariel {

Table::Table()
    : d(new TableData)
{
}

Table::Table(const QString &name)
    : d(new TableData)
{
    setName(name);
}


Table::Table(const TableData::Pointer &d)
    : d(d)
{
}

void Table::setName(const QString &name)
{
    d->name = name;
}

QString Table::name() const
{
    return d->name;
}

SelectManager Table::from() const
{
    return SelectManager(data());
}

SelectManager Table::select(const Attribute &projection) const
{
    return from().select(projection);
}

SelectManager Table::select(const QList<Attribute> &projections) const
{
    return from().select(projections);
}

SelectManager Table::select(std::initializer_list<Attribute> projections) const
{
    return from().select(projections);
}

SelectManager Table::select(const QString &projection) const
{
    return from().select(projection);
}

SelectManager Table::select(const QStringList &projections) const
{
    return from().select(projections);
}

SelectManager Table::select(std::initializer_list<const char *> projections) const
{
    return from().select(projections);
}

SelectManager Table::select(const SqlLiteral::Pointer &sqlLiteral) const
{
    return from().select(sqlLiteral);
}

SelectManager Table::select(const AbstractFunction::Pointer &function) const
{
    return from().select(function);
}

SelectManager Table::order(const AbstractOrder::Pointer &order) const
{
    return from().order(order);
}

SelectManager Table::where(const Attribute &attribute) const
{
    return from().where(attribute);
}

SelectManager Table::where(const ComparisonOperator &op) const
{
    return from().where(op);
}

SelectManager Table::where(const LogicalOperator &op) const
{
    return from().where(op);
}

SelectManager Table::group(const Attribute &attribute) const
{
    return from().group(attribute);
}

SelectManager Table::group(const QList<Attribute> &attributes) const
{
    return from().group(attributes);
}

SelectManager Table::group(std::initializer_list<Attribute> attributes) const
{
    return from().group(attributes);
}

SelectManager Table::take(int limit) const
{
    return from().take(limit);
}

SelectManager Table::skip(int offset) const
{
    return from().skip(offset);
}

InsertManager Table::insert(const Attribute &attribute, const QVariant &value) const
{
    return insertManager().insert(attribute, value);
}

InsertManager Table::insert(const Attribute &attribute, const BindValue &value) const
{
    return insertManager().insert(attribute, value);
}

UpdateManager Table::update(const Attribute &attribute, const QVariant &value) const
{
    return updateManager().update(attribute, value);
}

UpdateManager Table::update(const Attribute &attribute, const BindValue &value) const
{
    return updateManager().update(attribute, value);
}

DeleteManager Table::deleteWhere(const ComparisonOperator &op) const
{
    return deleteManager().where(op);
}

DeleteManager Table::deleteWhere(const LogicalOperator &op) const
{
    return deleteManager().where(op);
}

DeleteManager Table::deleteWhere(const Not::Pointer &op) const
{
    return deleteManager().where(op);
}

TableNode::Pointer Table::toNode() const
{
    return TableNode::create(d);
}

Attribute Table::operator[](const QString &name) const
{
    return Attribute(name, d);
}

bool Table::operator ==(const Table &other) const
{
    return *d == *other.d;
}

TableData::Pointer Table::data() const
{
    return d;
}

InsertManager Table::insertManager() const
{
    return InsertManager(d);
}

UpdateManager Table::updateManager() const
{
    return UpdateManager(d);
}

DeleteManager Table::deleteManager() const
{
    return DeleteManager(d);
}

} // namespace Ariel
