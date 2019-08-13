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

void Engine::addVisitor(const QString &driverName, AbstractVisitorCreator *creator)
{
    if (m_creators.contains(driverName))
        delete m_creators.take(driverName);

    m_creators.insert(driverName, creator);
}

std::unique_ptr<AbstractVisitor> Engine::visitor()
{
    auto creator = Engine::instance().defaultVisitorCreator();
    return creator->createVisitor();
}

std::unique_ptr<AbstractVisitor> Engine::visitor(const QString &driverName)
{
    const auto creator = Engine::instance().visitorCreator(driverName);
    return creator->createVisitor();
}

void Engine::setDefaultVisitorCreator(std::unique_ptr<AbstractVisitorCreator> creator)
{
    m_defaultCreator = std::move(creator);
}

AbstractVisitorCreator *Engine::defaultVisitorCreator() const
{
    return m_defaultCreator.get();
}

AbstractVisitorCreator *Engine::visitorCreator(const QString &driverName) const
{
    if (const auto creator = m_creators.value(driverName))
        return creator;
    else
        return defaultVisitorCreator();
}

Engine::Engine()
{
    createVisitors();
}

Engine::~Engine()
{
    qDeleteAll(m_creators);
}

void Engine::createVisitors()
{
    setDefaultVisitorCreator(std::make_unique<VisitorCreator<SqlVisitor>>());
    addVisitor(DriverName::Sqlite, new VisitorCreator<SqliteVisitor>());
}

} // namespace Ariel
