#ifndef ABSTRACTVALUEFORMATTER_H
#define ABSTRACTVALUEFORMATTER_H

#include <QVariant>

namespace Ariel {

class AbstractValueFormatter
{
public:
    virtual ~AbstractValueFormatter() = default;
    virtual QString escapeIdentifier(const QString &identifier) const = 0;
    virtual QString formatValue(const QVariant &value) const = 0;
};


class QuoteFormatter : public AbstractValueFormatter
{
public:
    QString escapeIdentifier(const QString &identifier) const override;
    QString formatValue(const QVariant &value) const override;
};

} // namespace Ariel

#endif // ABSTRACTVALUEFORMATTER_H
