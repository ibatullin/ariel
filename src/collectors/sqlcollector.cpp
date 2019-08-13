#include "sqlcollector.h"

#include "../formatters/sqldriverformatter.h"
#include <QSqlDriver>

namespace Ariel {

SqlCollector::SqlCollector(QSqlDriver *driver)
    : AbstractCollector(std::make_unique<SqlDriverFormatter>(driver))
{
}

QVariantList SqlCollector::boundValues() const
{
    return m_binds;
}

void SqlCollector::addBindValue(const QVariant &value)
{
    m_binds.append(value);
    collect("?");
}

} // namespace Ariel
