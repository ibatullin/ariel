#ifndef LITERALS_H
#define LITERALS_H

#include "table.h"
#include "bindvalue.h"

namespace Ariel {
namespace Literals {

Ariel::Table operator "" _table(const char *value, size_t)
{
    return Ariel::Table(value);
}

Ariel::BindValue operator ""_bind(const char *value, size_t)
{
    return Ariel::BindValue(QString(value));
}

Ariel::BindValue operator ""_bind(unsigned long long int value)
{
    return Ariel::BindValue(QVariant(value));
}

} // namespace Literals
} // namespace Ariel

#endif // LITERALS_H
