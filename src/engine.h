#ifndef ENGINE_H
#define ENGINE_H

#include "visitors/abstractvisitor.h"

#include <QString>
#include <QHash>

namespace Ariel {

class AbstractVisitorCreator
{
public:
    virtual ~AbstractVisitorCreator() = default;
    virtual std::unique_ptr<AbstractVisitor> createVisitor() const = 0;
};


template<typename T,
         typename = typename std::enable_if<std::is_base_of<AbstractVisitor, T>::value>::type>
class VisitorCreator : public AbstractVisitorCreator
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
    void addVisitor(const QString &driverName, AbstractVisitorCreator *creator);

    static std::unique_ptr<AbstractVisitor> visitor();
    static std::unique_ptr<AbstractVisitor> visitor(const QString &driverName);

protected:
    void setDefaultVisitorCreator(std::unique_ptr<AbstractVisitorCreator> creator);
    AbstractVisitorCreator *defaultVisitorCreator() const;
    AbstractVisitorCreator *visitorCreator(const QString &driverName) const;

private:
    Engine();
    ~Engine();
    void createVisitors();

    QString m_defaultType;
    std::unique_ptr<AbstractVisitorCreator> m_defaultCreator;
    QHash<QString, AbstractVisitorCreator *> m_creators;
};

} // namespace Ariel

#endif // ENGINE_H
