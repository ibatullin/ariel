#ifndef SQLDRIVERFORMATTER_H
#define SQLDRIVERFORMATTER_H

#include "abstractvalueformatter.h"
#include <QSqlDriver>
#include <QSqlField>
#include <QPointer>

namespace Ariel {

class SqlDriverFormatter : public AbstractValueFormatter
{
public:
    explicit SqlDriverFormatter(QSqlDriver *driver);
    QString escapeIdentifier(const QString &identifier) const override;
    QString formatValue(const QVariant &value) const override;

private:
    QPointer<QSqlDriver> m_driver;
};

} // namespace Ariel

#endif // SQLDRIVERFORMATTER_H
