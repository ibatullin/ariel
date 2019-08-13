#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "storage.h"
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");

    bool ok = db.open();
    Q_ASSERT(ok);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                       if (!obj && url == objUrl)
                         QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine.load(url);

    Storage storage;
    storage.createDatabase();

    QSqlQuery query(collector.value());
    query.exec();

    return app.exec();
}
