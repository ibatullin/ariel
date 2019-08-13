#ifndef BINDVALUE_H
#define BINDVALUE_H

#include "nodes/bindvalue.h"

namespace Ariel {

class BindValue
{
public:
    explicit BindValue(const QVariant &value);
    explicit BindValue(BindValueData::Pointer d);
    void setValue(const QVariant &value);
    QVariant value() const;
    void detach();
    BindValueNode::Pointer toNode() const;
    bool isValid() const;
    bool isNull() const;

private:
    BindValueData::Pointer d;
};

} // namespace Ariel

#endif // BINDVALUE_H
