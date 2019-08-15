#ifndef SELECTMANAGER_H
#define SELECTMANAGER_H

#include "treemanager.h"
#include "nodes/selectstatement.h"

namespace Ariel {

class TableData;
class Attribute;
class LogicalOperator;
class ComparisonOperator;

class SelectManager : public TreeManager<SelectStatement>
{
public:
    explicit SelectManager(const Table &table);
    explicit SelectManager(TableData::Pointer table);

    void setProjection(const Attribute &projection);
    void setOrder(AbstractOrder::Pointer order);
    void setWhere(const ComparisonOperator &op);
    void setWhere(const LogicalOperator &op);
    void setWhere(Not::Pointer op);
    void setGroup(const Attribute &attribute);
    void setLimit(Limit::Pointer limit);
    Limit::Pointer limit() const;
    void setOffset(Offset::Pointer offset);
    Offset::Pointer offset() const;

    SelectManager &from(const Table &table);
    SelectManager &from(TableData::Pointer table);
    SelectManager &select(const Attribute &projection);
    SelectManager &select(const QList<Attribute> &projections);
    SelectManager &select(std::initializer_list<Attribute> projections);
    SelectManager &select(const QString &projection);
    SelectManager &select(const QStringList &projections);
    SelectManager &select(std::initializer_list<const char *> projections);
    SelectManager &select(SqlLiteral::Pointer sqlLiteral);
    SelectManager &order(AbstractOrder::Pointer order);
    SelectManager &where(const Attribute &attribute);
    SelectManager &where(const ComparisonOperator &op);
    SelectManager &where(const LogicalOperator &op);
    SelectManager &where(Not::Pointer op);
    SelectManager &group(const Attribute &attribute);
    SelectManager &group(const QList<Attribute> &attributes);
    SelectManager &group(std::initializer_list<Attribute> attributes);
    SelectManager &group(const QString &attribute);
    SelectManager &group(const QStringList &attributes);
    SelectManager &group(std::initializer_list<const char *> attributes);
    SelectManager &take(int limit);
    SelectManager &take(Limit::Pointer limit);
    SelectManager &skip(int offset);
    SelectManager &skip(Offset::Pointer skip);

    SelectManager &distinctUnion(SelectCore::Pointer core);
    SelectManager &unionAll(SelectCore::Pointer core);
    SelectManager &intersect(SelectCore::Pointer core);
    SelectManager &except(SelectCore::Pointer core);

    SelectManager &distinctUnion(const SelectManager &other);
    SelectManager &unionAll(const SelectManager &other);
    SelectManager &intersect(const SelectManager &other);
    SelectManager &except(const SelectManager &other);

    static SelectManager distinctUnion(SelectManager lhs, const SelectManager &rhs);
    static SelectManager unionAll(SelectManager lhs, const SelectManager &rhs);
    static SelectManager intersect(SelectManager lhs, const SelectManager &rhs);
    static SelectManager except(SelectManager lhs, const SelectManager &rhs);

    SelectCore::Pointer context() const;

private:
    TableData::Pointer m_table;
};

} // namespace Ariel

#endif // SELECTMANAGER_H
