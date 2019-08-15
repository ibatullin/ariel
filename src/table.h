#ifndef TABLE_H
#define TABLE_H

#include "selectmanager.h"
#include "insertmanager.h"
#include "updatemanager.h"
#include "deletemanager.h"
#include "attribute.h"
#include "nodes/comparisonoperators.h"

#include <QString>
#include <QVector>

namespace Ariel {

static const QChar Star = QChar('*');

class TableData;

class Table
{
public:
    Table();
    explicit Table(const QString &name);
    explicit Table(TableData::Pointer d);
    void setName(const QString &name);
    QString name() const;

    SelectManager from() const;
    SelectManager select(const Attribute &projection) const;
    SelectManager select(const QList<Attribute> &projections) const;
    SelectManager select(std::initializer_list<Attribute> projections) const;
    SelectManager select(const QString &projection) const;
    SelectManager select(const QStringList &projections) const;
    SelectManager select(std::initializer_list<const char *> projections) const;
    SelectManager select(SqlLiteral::Pointer sqlLiteral) const;
    SelectManager order(AbstractOrder::Pointer order) const;
    SelectManager where(const Attribute &attribute) const;
    SelectManager where(const ComparisonOperator &op) const;
    SelectManager where(const LogicalOperator &op) const;
    SelectManager group(const Attribute &attribute) const;
    SelectManager group(const QList<Attribute> &attributes) const;
    SelectManager group(std::initializer_list<Attribute> attributes) const;
    SelectManager take(int limit) const;
    SelectManager skip(int offset) const;

    InsertManager insert(const Attribute &attribute, const QVariant &value) const;
    InsertManager insert(const Attribute &attribute, const BindValue &value) const;
    UpdateManager update(const Attribute &attribute, const QVariant &value) const;
    UpdateManager update(const Attribute &attribute, const BindValue &value) const;
    DeleteManager deleteWhere(const ComparisonOperator &op) const;
    DeleteManager deleteWhere(const LogicalOperator &op) const;
    DeleteManager deleteWhere(Not::Pointer op) const;

    TableNode::Pointer toNode() const;
    Attribute operator[](const QString &name) const;
    bool operator ==(const Table &other) const;
    TableData::Pointer data() const;

private:
    InsertManager insertManager() const;
    UpdateManager updateManager() const;
    DeleteManager deleteManager() const;

    TableData::Pointer d;
};

} // namespace Ariel

#endif // TABLE_H
