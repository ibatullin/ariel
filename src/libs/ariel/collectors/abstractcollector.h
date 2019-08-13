#ifndef ABSTRACTCOLLECTOR_H
#define ABSTRACTCOLLECTOR_H

#include "../formatters/abstractvalueformatter.h"

#include <QVariant>

#include <memory>

namespace Ariel {

class AbstractCollector
{
public:
    explicit AbstractCollector(std::unique_ptr<AbstractValueFormatter> formatter);
    AbstractCollector(AbstractCollector &&other) = default;
    virtual ~AbstractCollector() = default;
    void collect(const QString &s);
    void collect(const char *s);
    void formatValue(const QVariant &value);
    void escapeIdentifier(const QString &identifier);
    void bindValue(const QVariant &value);
    QString value() const;
    bool isEmpty() const;
    void clear();
    AbstractCollector &operator <<(const QString &s);
    AbstractCollector &operator <<(const char *s);

protected:
    virtual void addBindValue(const QVariant &value) = 0;
    AbstractValueFormatter *formatter() const;

private:
    QString m_value;
    std::unique_ptr<AbstractValueFormatter> m_formatter;
};


class StringCollector : public AbstractCollector
{
public:
    StringCollector();

private:
    void addBindValue(const QVariant &value) override;
};

} // namespace Ariel

#endif // ABSTRACTCOLLECTOR_H
