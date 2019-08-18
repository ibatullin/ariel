#ifndef BINDVALUENODE_H
#define BINDVALUENODE_H

#include "node.h"

namespace Ariel {

class BindValueData : public QSharedData
{
public:
    using Pointer = QExplicitlySharedDataPointer<BindValueData>;
    BindValueData() = default;
    explicit BindValueData(const QVariant &value);

    QVariant value;
};


class BindValueNode : public Node<BindValueNode>
{
public:
    BindValueNode() = default;
    explicit BindValueNode(const BindValueData::Pointer &d);
    BindValueNode(const BindValueNode &other);
    BindValueNode &operator =(BindValueNode other);
    void setValue(const QVariant &value);
    QVariant value() const;

private:
    BindValueData::Pointer d;
};

} // namespace Ariel


#endif // BINDVALUENODE_H
