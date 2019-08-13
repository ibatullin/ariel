#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H

#include <QSharedData>

namespace Ariel {

class AbstractVisitor;
class AbstractCollector;

class AbstractNode : public QSharedData
{
public:
    AbstractNode() = default;
    virtual ~AbstractNode() = default;
    virtual void accept(AbstractVisitor &visitor, AbstractCollector &collector)
    {
        Q_UNUSED(visitor);
        Q_UNUSED(collector);
    }

    virtual AbstractNode *clone() const
    {
        return nullptr;
    }

protected:
    template<typename T>
    static void copy(QExplicitlySharedDataPointer<T> &lhs, const QExplicitlySharedDataPointer<T> &rhs)
    {
        if (rhs) {
            auto x = static_cast<T *>(rhs->clone());
            Q_ASSERT(x);
            lhs = QExplicitlySharedDataPointer<T>(x);
        }
    }

    template<typename T>
    static void copy(QList<QExplicitlySharedDataPointer<T>> &lhs,
                     const QList<QExplicitlySharedDataPointer<T>> &rhs)
    {
        lhs.reserve(rhs.size());
        for (const auto &item : rhs) {
            if (item) {
                auto x = static_cast<T *>(item->clone());
                Q_ASSERT(x);
                lhs.append(QExplicitlySharedDataPointer<T>(x));
            } else {
                lhs.append(QExplicitlySharedDataPointer<T>());
            }
        }
    }
};

using NodePointer = QExplicitlySharedDataPointer<AbstractNode>;

template<typename T>
class NodeMethods
{
public:
    using Pointer = QExplicitlySharedDataPointer<T>;

    template<typename... Args>
    static inline Pointer create(const Args &... args)
    {
        return Pointer(new T(args...));
    }
};

#define ARIEL_DECLARE_CRTP(Class, Base) \
class Class : public Base<Class> \
{ \
public: \
    using Base<Class>::Base; \
};

} // namespace Ariel


#endif // ABSTRACTNODE_H
