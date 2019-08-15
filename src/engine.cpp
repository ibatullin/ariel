#include "engine.h"

#include "visitors/sqlvisitor.h"
#include "visitors/sqlitevisitor.h"

namespace Ariel {

namespace DriverName {

//const char Db2[]     = "QDB2";     // IBM DB2
//const char Ibase[]   = "QIBASE";   // Borland InterBase Driver
//const char Mysql[]   = "QMYSQL";   // MySQL Driver
//const char Oci[]     = "QOCI";     // Oracle Call Interface Driver
//const char Odbc[]    = "QODBC";    // ODBC Driver (includes Microsoft SQL Server)
//const char Psql[]    = "QPSQL";    // PostgreSQL Driver
const char Sqlite[]  = "QSQLITE";  // SQLite version 3 or above

}


Engine &Engine::instance()
{
    static Engine self;
    return self;
}

void Engine::setDefaultDriverName(const QString &type)
{
    m_defaultType = type;
}

QString Engine::defaultDriverName() const
{
    return m_defaultType;
}

void Engine::addVisitor(const QString &driverName, AbstractVisitorFactory *factory)
{
    if (m_factories.contains(driverName))
        delete m_factories.take(driverName);

    m_factories.insert(driverName, factory);
}

std::unique_ptr<AbstractVisitor> Engine::visitor()
{
    auto factory = Engine::instance().defaultVisitorFactory();
    return factory->createVisitor();
}

std::unique_ptr<AbstractVisitor> Engine::visitor(const QString &driverName)
{
    const auto factory = Engine::instance().visitorFactory(driverName);
    return factory->createVisitor();
}

void Engine::setDefaultVisitorFactory(std::unique_ptr<AbstractVisitorFactory> factory)
{
    m_defaultFactory = std::move(factory);
}

AbstractVisitorFactory *Engine::defaultVisitorFactory() const
{
    return m_defaultFactory.get();
}

AbstractVisitorFactory *Engine::visitorFactory(const QString &driverName) const
{
    if (const auto factory = m_factories.value(driverName))
        return factory;
    else
        return defaultVisitorFactory();
}

Engine::Engine()
{
    createVisitors();
}

Engine::~Engine()
{
    qDeleteAll(m_factories);
}

void Engine::createVisitors()
{
    setDefaultVisitorFactory(std::make_unique<VisitorFactory<SqlVisitor>>());
    addVisitor(DriverName::Sqlite, new VisitorFactory<SqliteVisitor>());
}

} // namespace Ariel
