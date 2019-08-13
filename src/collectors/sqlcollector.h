#ifndef SQLCOLLECTOR_H
#define SQLCOLLECTOR_H

#include "abstractcollector.h"

class QSqlDriver;

namespace Ariel {

class SqlDriverFormatter;

class SqlCollector : public AbstractCollector
{
public:
    explicit SqlCollector(QSqlDriver *driver);
    QVariantList boundValues() const;

private:
    void addBindValue(const QVariant &value) override;

    QVariantList m_binds;
};

} // namespace Ariel

#endif // SQLCOLLECTOR_H
