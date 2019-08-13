#include "sqldriverformatter.h"

namespace Ariel {

SqlDriverFormatter::SqlDriverFormatter(QSqlDriver *driver)
    : m_driver(driver)
{
}

QString SqlDriverFormatter::escapeIdentifier(const QString &identifier) const
{
    return m_driver->escapeIdentifier(identifier, QSqlDriver::IdentifierType::FieldName);
}

QString SqlDriverFormatter::formatValue(const QVariant &value) const
{
    Q_ASSERT(m_driver);
    QSqlField field(QString(), value.type());
    field.setValue(value);
    return m_driver->formatValue(field);
}

} // namespace Ariel
