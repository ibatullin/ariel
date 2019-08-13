#include "abstractcollector.h"

namespace Ariel {

AbstractCollector::AbstractCollector(std::unique_ptr<AbstractValueFormatter> formatter)
    : m_formatter(std::move(formatter))
{
}

void AbstractCollector::collect(const QString &s)
{
    m_value.append(s);
}

void AbstractCollector::collect(const char *s)
{
    m_value.append(s);
}

void AbstractCollector::formatValue(const QVariant &value)
{
    collect(formatter()->formatValue(value));
}

void AbstractCollector::escapeIdentifier(const QString &identifier)
{
    collect(formatter()->escapeIdentifier(identifier));
}

void AbstractCollector::bindValue(const QVariant &value)
{
    addBindValue(value);
}

QString AbstractCollector::value() const
{
    return m_value;
}

bool AbstractCollector::isEmpty() const
{
    return m_value.isEmpty();
}

void AbstractCollector::clear()
{
    m_value.clear();
}

AbstractCollector &AbstractCollector::operator <<(const char *s)
{
    collect(s);
    return *this;
}

AbstractCollector &AbstractCollector::operator <<(const QString &s)
{
    collect(s);
    return *this;
}

AbstractValueFormatter *AbstractCollector::formatter() const
{
    return m_formatter.get();
}



StringCollector::StringCollector()
    : AbstractCollector(std::make_unique<QuoteFormatter>())
{
}

void StringCollector::addBindValue(const QVariant &value)
{
    collect(formatter()->formatValue(value));
}

} // namespace Ariel
