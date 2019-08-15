#ifndef ATTRIBUTENODE_H
#define ATTRIBUTENODE_H

#include "node.h"
#include "../table_p.h"
#include "../visitors/abstractvisitor.h"

#include <QSharedData>
#include <QSharedDataPointer>

namespace Ariel {

class Table;

class AttributeData : public QSharedData
{
public:
    using Pointer = QExplicitlySharedDataPointer<AttributeData>;

    bool operator ==(const AttributeData &other) const
    {
        return name == other.name && *relation.data() == *other.relation.data();
    }

    QString name;
    TableData::Pointer relation;
};


template<typename T>
class BaseAttributeNode : public Node<T>
{
public:
    BaseAttributeNode()
        : d(new AttributeData)
    {
    }
    BaseAttributeNode(const BaseAttributeNode &other)
        : d(other.d)
    {
        d.detach();
    }

    explicit BaseAttributeNode(AttributeData::Pointer d)
        : d(d)
    {
    }

    AttributeNode &operator =(BaseAttributeNode<T> other)
    {
        std::swap(d, other.d);
        return *this;
    }

protected:
    AttributeData::Pointer data() const
    {
        return d;
    }

private:
    AttributeData::Pointer d;
};


class UnqualifiedColumn;

class AttributeNode : public BaseAttributeNode<AttributeNode>
{
public:
    using BaseAttributeNode<AttributeNode>::BaseAttributeNode;
    QString name() const;
    QString relation() const;
    QExplicitlySharedDataPointer<UnqualifiedColumn> toUnqualifideColumnNode() const;
};



class UnqualifiedColumn : public BaseAttributeNode<UnqualifiedColumn>
{
public:
    using BaseAttributeNode<UnqualifiedColumn>::BaseAttributeNode;
    QString name() const;
    AttributeNode::Pointer toAttributeNode() const;
};

} // namespace Ariel

#endif // ATTRIBUTENODE_H
