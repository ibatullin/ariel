#include "treemanager.h"
#include "engine.h"

#include <QSqlDatabase>
#include <QDebug>

namespace Ariel {

SqlCollector AbstractTreeManager::build() const
{
    return build(QSqlDatabase::database());
}

SqlCollector AbstractTreeManager::build(const QSqlDatabase &db) const
{
    Q_ASSERT(db.driver());
    SqlCollector collector(db.driver());
    collect(db, collector);
    return collector;
}

void AbstractTreeManager::collect(AbstractCollector &collector) const
{
    auto visitor = Engine::visitor();
    collect(visitor.get(), collector);
}

void AbstractTreeManager::collect(const QSqlDatabase &db, AbstractCollector &collector) const
{
    auto visitor = Engine::visitor(db.driverName());
    collect(visitor.get(), collector);
}

void AbstractTreeManager::collect(AbstractVisitor *visitor, AbstractCollector &collector) const
{
    collector.clear();
    accept(visitor, collector);
}

QString AbstractTreeManager::toString() const
{
    StringCollector collector;
    collect(collector);
    return collector.value();
}

QString AbstractTreeManager::toSql() const
{
    return toSql(QSqlDatabase::database());
}

QString AbstractTreeManager::toSql(const QSqlDatabase &db) const
{
    return build(db).value();
}

} // namespace Ariel


QDebug operator<<(QDebug debug, const Ariel::AbstractTreeManager &manager)
{
    debug << manager.toSql();
    return debug;
}
