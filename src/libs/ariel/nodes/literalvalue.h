#ifndef LITERALVALUE_H
#define LITERALVALUE_H

#include "node.h"

#include <QVariant>

namespace Ariel {

template<typename T>
class BaseLiteral : public Node<T>
{
public:
    explicit BaseLiteral(const QVariant &value)
        : m_value(value)
    {
    }
    void setValue(const QVariant &value)
    {
        m_value = value;
    }
    QVariant value() const
    {
        return m_value;
    }

private:
    QVariant m_value;
};


class LiteralValue : public BaseLiteral<LiteralValue>
{
public:
    using BaseLiteral<LiteralValue>::BaseLiteral;
    static NodePointer valueNode(const QVariant &value);
    static NodePointer valueOrListNode(const QVariant &value);
};

ARIEL_DECLARE_CRTP(SqlLiteral, BaseLiteral)


template<typename T>
class List : public Node<List<T>>
{
public:
    explicit List(const QList<T> &list)
        : m_list(list)
    {
    }

    QList<T> list() const
    {
        return m_list;
    }

    void append(const T &item)
    {
        m_list.append(item);
    }

    void clear()
    {
        m_list.clear();
    }

private:
    QList<T> m_list;
};

using VariantList = List<QVariant>;
using StringList = List<QString>;

ARIEL_DECLARE_CRTP(True, Node)
ARIEL_DECLARE_CRTP(False, Node)
ARIEL_DECLARE_CRTP(Null, Node)

} // namespace Ariel


#endif // LITERALVALUE_H
