#include "abstractvalueformatter.h"

namespace Ariel {

QString QuoteFormatter::escapeIdentifier(const QString &identifier) const
{
    return identifier;
}

QString QuoteFormatter::formatValue(const QVariant &value) const
{
    switch (value.type()) {
    case QVariant::Type::Char:
    case QVariant::Type::Date:
    case QVariant::Type::DateTime:
    case QVariant::Type::RegExp:
    case QVariant::Type::RegularExpression:
    case QVariant::Type::String:
    case QVariant::Type::Time:
    case QVariant::Type::Url:
    case QVariant::Type::Uuid:
        return '\'' + value.toString() + '\'';
    default:
        return value.toString();
    }
}

} // namespace Ariel
