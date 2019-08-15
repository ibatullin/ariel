#ifndef ENGINE_H
#define ENGINE_H

#include "visitors/abstractvisitor.h"

#include <QString>
#include <QHash>

namespace Ariel {

class AbstractVisitorFactory
{
public:
    virtual ~AbstractVisitorFactory() = default;
    virtual std::unique_ptr<AbstractVisitor> createVisitor() const = 0;
};


template<typename T,
         typename = typename std::enable_if<std::is_base_of<AbstractVisitor, T>::value>::type>
class VisitorFactory : public AbstractVisitorFactory
{
public:
    std::unique_ptr<AbstractVisitor> createVisitor() const override
    {
        return std::make_unique<T>();
    }
};


class Engine
{
public:
    static Engine &instance();

    Engine(const Engine &) = delete;
    Engine(Engine &&) = delete;

    Engine &operator =(const Engine &) = delete;
    Engine &operator =(Engine &&) = delete;

    void setDefaultDriverName(const QString &type);
    QString defaultDriverName() const;
    void addVisitor(const QString &driverName, AbstractVisitorFactory *factory);

    static std::unique_ptr<AbstractVisitor> visitor();
    static std::unique_ptr<AbstractVisitor> visitor(const QString &driverName);

protected:
    void setDefaultVisitorFactory(std::unique_ptr<AbstractVisitorFactory> factory);
    AbstractVisitorFactory *defaultVisitorFactory() const;
    AbstractVisitorFactory *visitorFactory(const QString &driverName) const;

private:
    Engine();
    ~Engine();
    void createVisitors();

    QString m_defaultType;
    std::unique_ptr<AbstractVisitorFactory> m_defaultFactory;
    QHash<QString, AbstractVisitorFactory *> m_factories;
};

} // namespace Ariel

#endif // ENGINE_H
