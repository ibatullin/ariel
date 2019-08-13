#include <QtTest>

#include "table.h"
#include "selectmanager.h"
#include "insertmanager.h"
#include "updatemanager.h"
#include "deletemanager.h"
#include "bindvalue.h"
#include "collectors/sqlcollector.h"

#include <QDateTime>
#include <QSqlDatabase>

using namespace Ariel;

class ArielTest : public QObject
{
    Q_OBJECT
public:
    ArielTest();

private slots:
    void projection();
    void projection_data();
    void where();
    void where_data();
    void comparisonOperators();
    void comparisonOperators_data();
    void logicalOperators();
    void logicalOperators_data();
    void comparisonTypes();
    void comparisonTypes_data();
    void order();
    void order_data();
    void groupBy();
    void groupBy_data();
    void limitOffset();
    void limitOffset_data();
    void detach();
    void compoundSelectStatement();
    void compoundSelectStatement_data();

    void insert();
    void insert_data();
    void update();
    void update_data();
    void deleteStatement();
    void deleteStatement_data();

    void sqlite();
    void bindings();

private:
    QString resultSql(const QString &where)
    {
        const QString baseSql("SELECT posts.* FROM posts WHERE ");
        return baseSql + where;
    }

    template<typename T>
    QString where(const T &op) const
    {
        return posts
            .select(Ariel::Star)
            .where(op)
            .toSql();
    }

    const Table posts;
    const Table users;
    const Attribute column1;
    const Attribute column2;
    const Attribute column3;
    const Attribute column4;
};


ArielTest::ArielTest()
    : posts("posts"),
      users("users"),
      column1(posts["column1"]),
      column2(posts["column2"]),
      column3(posts["column3"]),
      column4(users["column4"])
{
}

void ArielTest::projection()
{
    QFETCH(QString, sql);
    QFETCH(QString, result);
    QCOMPARE(sql, result);
}

void ArielTest::projection_data()
{
    QTest::addColumn<QString>("sql");
    QTest::addColumn<QString>("result");

    QTest::newRow("star")
        << posts.select(Ariel::Star).toSql()
        << QStringLiteral("SELECT posts.* FROM posts");

    QTest::newRow("attribute")
        << posts.select(column1).toSql()
        << QStringLiteral("SELECT posts.column1 FROM posts");

    QTest::newRow("attributes")
        << posts.select(column1).select(column2).toSql()
        << QStringLiteral("SELECT posts.column1, posts.column2 FROM posts");

    QTest::newRow("initalizer list")
        << posts.select({ "column1", "column2" }).toSql()
        << QStringLiteral("SELECT posts.column1, posts.column2 FROM posts");

    QTest::newRow("QStringList")
        << posts.select(QStringList { "column1", "column2" }).toSql()
        << QStringLiteral("SELECT posts.column1, posts.column2 FROM posts");
}

void ArielTest::where()
{
    QFETCH(QString, sql);
    QFETCH(QString, result);
    QCOMPARE(sql, resultSql(result));
}

void ArielTest::where_data()
{
    QTest::addColumn<QString>("sql");
    QTest::addColumn<QString>("result");

    // In
    QStringList stringList{ "a", "b", "c" };
    QVariantList variantList { "a", "b", 1, 2 };

    QTest::newRow("a1 in (stringList)")
        << where(column1.in(stringList))
        << QStringLiteral("posts.column1 IN ('a', 'b', 'c')");

    QTest::newRow("a1 in (variantList)")
        << where(column1.in(variantList))
        << QStringLiteral("posts.column1 IN ('a', 'b', 1, 2)");

    QTest::newRow("a1 not in (stringList)")
        << where(column1.notIn(stringList))
        << QStringLiteral("posts.column1 NOT IN ('a', 'b', 'c')");

    QTest::newRow("a1 not in (variantList)")
        << where(column1.notIn(variantList))
        << QStringLiteral("posts.column1 NOT IN ('a', 'b', 1, 2)");


    QTest::newRow("a1 != list")
        << where(column1 != stringList)
        << QStringLiteral("posts.column1 NOT IN ('a', 'b', 'c')");

    QTest::newRow("a1 != (variantList)")
        << where(column1 != variantList)
        << QStringLiteral("posts.column1 NOT IN ('a', 'b', 1, 2)");
}

void ArielTest::comparisonOperators()
{
    QFETCH(QString, sql);
    QFETCH(QString, result);
    QCOMPARE(sql, resultSql(result));
}

void ArielTest::comparisonOperators_data()
{
    QTest::addColumn<QString>("sql");
    QTest::addColumn<QString>("result");

    QTest::newRow("a")
        << where(column1)
        << QStringLiteral("posts.column1 = TRUE");

    QTest::newRow("!a")
        << where(!column1)
        << QStringLiteral("posts.column1 = FALSE");


    // Comparison with values

    QTest::newRow("a == 1")
        << where(column1 == 1)
        << QStringLiteral("posts.column1 = 1");

    QTest::newRow("a != 1")
        << where(column1 != 1)
        << QStringLiteral("posts.column1 <> 1");

    QTest::newRow("a < 1")
        << where(column1 < 1)
        << QStringLiteral("posts.column1 < 1");

    QTest::newRow("a > 1")
        << where(column1 > 1)
        << QStringLiteral("posts.column1 > 1");

    QTest::newRow("a <= 1")
        << where(column1 <= 1)
        << QStringLiteral("posts.column1 <= 1");

    QTest::newRow("a >= 1")
        << where(column1 >= 1)
        << QStringLiteral("posts.column1 >= 1");


    // Comparison with attribute

    QTest::newRow("a1 == a2")
        << where(column1 == column2)
        << QStringLiteral("posts.column1 = posts.column2");

    QTest::newRow("a1 != a2")
        << where(column1 != column2)
        << QStringLiteral("posts.column1 <> posts.column2");

    QTest::newRow("a1 < a2")
        << where(column1 < column2)
        << QStringLiteral("posts.column1 < posts.column2");

    QTest::newRow("a1 <= a2")
        << where(column1 <= column2)
        << QStringLiteral("posts.column1 <= posts.column2");

    QTest::newRow("a1 > a2")
        << where(column1 > column2)
        << QStringLiteral("posts.column1 > posts.column2");

    QTest::newRow("a1 >= a2")
        << where(column1 >= column2)
        << QStringLiteral("posts.column1 >= posts.column2");


    // Special comparison operators

    QTest::newRow("a is null")
        << where(column1.isNull())
        << QStringLiteral("posts.column1 IS NULL");

    QTest::newRow("a is not null")
        << where(column1.isNotNull())
        << QStringLiteral("posts.column1 IS NOT NULL");

    QTest::newRow("between")
        << where(column1.between(1, 2))
        << QStringLiteral("posts.column1 BETWEEN 1 AND 2");

    QTest::newRow("match")
        << where(column1.match("a%"))
        << QStringLiteral("posts.column1 LIKE 'a%'");

    QTest::newRow("in")
        << where(column1.in("a"))
        << QStringLiteral("posts.column1 IN ('a')");

    QTest::newRow("not in")
        << where(column1.notIn("a"))
        << QStringLiteral("posts.column1 NOT IN ('a')");


    QTest::newRow("!(a is null)")
        << where(!column1.isNull())
        << QStringLiteral("posts.column1 IS NOT NULL");

    QTest::newRow("!(a is not null)")
        << where(!column1.isNotNull())
        << QStringLiteral("posts.column1 IS NULL");

    QTest::newRow("!between")
        << where(!column1.between(1, 2))
        << QStringLiteral("posts.column1 NOT BETWEEN 1 AND 2");

    QTest::newRow("!match")
        << where(!column1.match("a%"))
        << QStringLiteral("posts.column1 NOT LIKE 'a%'");

    QTest::newRow("!in")
        << where(!column1.in("a"))
        << QStringLiteral("posts.column1 NOT IN ('a')");

    QTest::newRow("!(not in)")
        << where(!column1.notIn("a"))
        << QStringLiteral("posts.column1 IN ('a')");


    QTest::newRow("!!(a is null)")
        << where(!!column1.isNull())
        << QStringLiteral("posts.column1 IS NULL");

    QTest::newRow("!!(a is not null)")
        << where(!!column1.isNotNull())
        << QStringLiteral("posts.column1 IS NOT NULL");

    QTest::newRow("!!between")
        << where(!!column1.between(1, 2))
        << QStringLiteral("posts.column1 BETWEEN 1 AND 2");

    QTest::newRow("!!match")
        << where(!!column1.match("a%"))
        << QStringLiteral("posts.column1 LIKE 'a%'");

    QTest::newRow("!!in")
        << where(!!column1.in("a"))
        << QStringLiteral("posts.column1 IN ('a')");

    QTest::newRow("!!(not in)")
        << where(!!column1.notIn("a"))
        << QStringLiteral("posts.column1 NOT IN ('a')");
}

void ArielTest::logicalOperators()
{
    QFETCH(QString, sql);
    QFETCH(QString, result);
    QCOMPARE(sql, resultSql(result));
}

void ArielTest::logicalOperators_data()
{
    QTest::addColumn<QString>("sql");
    QTest::addColumn<QString>("result");

    const auto comparison = column1 > 1;
    const auto logical = column2 > 1 && column3 > 1;
    const QString comparisonSql = "posts.column1 > 1";
    const QString logicalSql = "posts.column2 > 1 AND posts.column3 > 1";

    // And
    QTest::newRow("comparison && comparison")
        << where(comparison && comparison)
        << QString("%1 AND %2")
               .arg(comparisonSql)
               .arg(comparisonSql);

    QTest::newRow("comparison && logical")
        << where(comparison && logical)
        << QString("%1 AND (%2)")
               .arg(comparisonSql)
               .arg(logicalSql);

    QTest::newRow("logical && comparison")
        << where(logical && comparison)
        << QString("%1 AND %2")
               .arg(logicalSql)
               .arg(comparisonSql);

    QTest::newRow("logical && logical")
        << where(logical && logical)
        << QString("(%1) AND (%2)")
               .arg(logicalSql)
               .arg(logicalSql);


    // Or
    QTest::newRow("comparison || comparison")
        << where(comparison || comparison)
        << QString("%1 OR %2")
               .arg(comparisonSql)
               .arg(comparisonSql);

    QTest::newRow("comparison || logical")
        << where(comparison || logical)
        << QString("%1 OR (%2)")
               .arg(comparisonSql)
               .arg(logicalSql);

    QTest::newRow("logical || comparison")
        << where(logical || comparison)
        << QString("%1 OR %2")
               .arg(logicalSql)
               .arg(comparisonSql);

    QTest::newRow("logical || logical")
        << where(logical || logical)
        << QString("(%1) OR (%2)")
               .arg(logicalSql)
               .arg(logicalSql);


    QTest::newRow("a > 1 && b > 1")
        << where(column1 > 1 && column2 > 1)
        << QStringLiteral("posts.column1 > 1 AND posts.column2 > 1");

    QTest::newRow("a > 1 || b > 1")
        << where(column1 > 1 && column2 > 1)
        << QStringLiteral("posts.column1 > 1 AND posts.column2 > 1");

    QTest::newRow("!comparison")
        << where(!comparison)
        << "NOT " + comparisonSql;

    QTest::newRow("!logical")
        << where(!logical)
        << QString("NOT (%1)").arg(logicalSql);


    QTest::newRow("a > 1 && b > 1 && c > 1")
        << where(column1 > 1 && column2 > 1 && column3 > 1)
        << QStringLiteral("posts.column1 > 1 AND posts.column2 > 1 AND posts.column3 > 1");

    QTest::newRow("a > 1 && b > 1 || c > 1")
        << where(column1 > 1 && column2 > 1 || column3 > 1)
        << QStringLiteral("posts.column1 > 1 AND posts.column2 > 1 OR posts.column3 > 1");

    QTest::newRow("a > 1 || b > 1 && c > 1")
        << where(column1 > 1 || column2 > 1 && column3 > 1)
        << QStringLiteral("posts.column1 > 1 OR (posts.column2 > 1 AND posts.column3 > 1)");

    QTest::newRow("a > 1 || b > 1 || c > 1")
        << where(column1 > 1 || column2 > 1 || column3 > 1)
        << QStringLiteral("posts.column1 > 1 OR posts.column2 > 1 OR posts.column3 > 1");
}

void ArielTest::comparisonTypes()
{
    QFETCH(QString, sql);
    QFETCH(QString, result);
    QCOMPARE(sql, resultSql(result));
}

void ArielTest::comparisonTypes_data()
{
    QTest::addColumn<QString>("sql");
    QTest::addColumn<QString>("result");

    QTest::newRow("a == 'A'")
        << where(column1 == "A")
        << QStringLiteral("posts.column1 = 'A'");

    QTest::newRow("a == QString")
        << where(column1 == QString("A"))
        << QStringLiteral("posts.column1 = 'A'");

    QTest::newRow("a == QVariant(int)")
        << where(column1 == QVariant(1))
        << QStringLiteral("posts.column1 = 1");

    QTest::newRow("a == QDate")
        << where(column1 == QDate::fromString("02.03.2019", "dd.MM.yyyy"))
        << QStringLiteral("posts.column1 = '2019-03-02'");

    QTest::newRow("a == invalid QVariant")
        << where(column1 == QVariant())
        << QStringLiteral("posts.column1 IS NULL");


    QStringList stringList{ "a", "b", "c" };
    QVariantList variantList { "a", "b", 1, 2 };

    QTest::newRow("a1 == list")
        << where(column1 == stringList)
        << QStringLiteral("posts.column1 IN ('a', 'b', 'c')");

    QTest::newRow("a1 == (variantList)")
        << where(column1 == variantList)
        << QStringLiteral("posts.column1 IN ('a', 'b', 1, 2)");
}

void ArielTest::order()
{
    QFETCH(QString, sql);
    QFETCH(QString, result);
    QCOMPARE(sql, result);
}

void ArielTest::order_data()
{
    QTest::addColumn<QString>("sql");
    QTest::addColumn<QString>("result");

    QTest::newRow("asc")
        << posts
               .select(Ariel::Star)
               .order(column1.ascending())
               .toSql()
        << QStringLiteral("SELECT posts.* FROM posts ORDER BY posts.column1 ASC");

    QTest::newRow("desc")
        << posts
               .select(Ariel::Star)
               .order(column1.descending())
               .toSql()
        << QStringLiteral("SELECT posts.* FROM posts ORDER BY posts.column1 DESC");

    QTest::newRow("asc, asc")
        << posts
               .select(Ariel::Star)
               .order(column1.ascending())
               .order(column2.ascending())
               .toSql()
        << QStringLiteral("SELECT posts.* FROM posts ORDER BY posts.column1 ASC, posts.column2 ASC");

}

void ArielTest::groupBy()
{
    QFETCH(QString, sql);
    QFETCH(QString, result);
    QCOMPARE(sql, result);
}

void ArielTest::groupBy_data()
{
    QTest::addColumn<QString>("sql");
    QTest::addColumn<QString>("result");

    QTest::newRow("a1")
        << posts.select(Ariel::Star).group(column1).toSql()
        << QStringLiteral("SELECT posts.* FROM posts GROUP BY posts.column1");

    QTest::newRow("a1, a2")
        << posts.select(Ariel::Star).group(column1).group(column2).toSql()
        << QStringLiteral("SELECT posts.* FROM posts GROUP BY posts.column1, posts.column2");

    QTest::newRow("{ a1, a2 }")
        << posts.select(Ariel::Star).group({ column1, column2 }).toSql()
        << QStringLiteral("SELECT posts.* FROM posts GROUP BY posts.column1, posts.column2");

    QTest::newRow("QList { a1, a2 }")
        << posts.select(Ariel::Star).group(QList<Attribute> { column1, column2 }).toSql()
        << QStringLiteral("SELECT posts.* FROM posts GROUP BY posts.column1, posts.column2");

    QTest::newRow("QString")
        << posts.select(Ariel::Star).group(QString("column1")).toSql()
        << QStringLiteral("SELECT posts.* FROM posts GROUP BY posts.column1");

    QTest::newRow("QStringList")
        << posts.select(Ariel::Star).group(QStringList { "column1", "column2" }).toSql()
        << QStringLiteral("SELECT posts.* FROM posts GROUP BY posts.column1, posts.column2");

    QTest::newRow("initializer_list<const char *>")
        << posts.select(Ariel::Star).group({ "column1", "column2" }).toSql()
        << QStringLiteral("SELECT posts.* FROM posts GROUP BY posts.column1, posts.column2");
}

void ArielTest::limitOffset()
{
    QFETCH(QString, sql);
    QFETCH(QString, result);
    QCOMPARE(sql, result);
}

void ArielTest::limitOffset_data()
{
    QTest::addColumn<QString>("sql");
    QTest::addColumn<QString>("result");

    QTest::newRow("limit")
        << posts.select(Ariel::Star).take(1).toSql()
        << QStringLiteral("SELECT posts.* FROM posts LIMIT 1");

    QTest::newRow("offset")
        << posts.select(Ariel::Star).skip(1).toSql()
        << QStringLiteral("SELECT posts.* FROM posts OFFSET 1");

    QTest::newRow("limit offset")
        << posts.select(Ariel::Star).take(1).skip(2).toSql()
        << QStringLiteral("SELECT posts.* FROM posts LIMIT 1 OFFSET 2");
}

void ArielTest::detach()
{
    auto limit = Limit::create(LiteralValue::create(1));
    auto select1 = posts
                       .select({ column1, column2 })
                       .where(column1 == 1 && column2 < 2)
                       .order(column2.ascending())
                       .group(column3)
                       .take(limit)
                       .skip(3);
    SelectManager select2(select1);

    QVERIFY(select1.limit()  = select2.limit());
    QVERIFY(select1.offset() = select2.offset());
    QCOMPARE(select1.toSql(), select2.toSql());

    select2.detach();
    QVERIFY(select1.limit()  != select2.limit());
    QVERIFY(select1.offset() != select2.offset());
    QCOMPARE(select1.toSql(), select2.toSql());

    limit->setExpression(LiteralValue::create(2));
    QVERIFY(select1.toSql() != select2.toSql());

    select2.setOrder(column3.descending());
    auto select3 = SelectManager::distinctUnion(select1, select2);
    QCOMPARE(select3.toSql(),
             QString("SELECT posts.column1, posts.column2 FROM posts"
                     " WHERE posts.column1 = 1 AND posts.column2 < 2"
                     " GROUP BY posts.column3"
                     " UNION"
                     " SELECT posts.column1, posts.column2 FROM posts"
                     " WHERE posts.column1 = 1 AND posts.column2 < 2"
                     " GROUP BY posts.column3"
                     " ORDER BY posts.column2 ASC, posts.column3 DESC"
                     " LIMIT 2 OFFSET 3"));
}

void ArielTest::compoundSelectStatement()
{
    QFETCH(QString, sql);
    QFETCH(QString, result);
    QCOMPARE(sql, result);
}

void ArielTest::compoundSelectStatement_data()
{
    QTest::addColumn<QString>("sql");
    QTest::addColumn<QString>("result");

    const auto select1 = posts.select(column1).where(column1 == 1);
    const auto select2 = posts.select(column2).where(column2 == 2);

    QTest::newRow("union")
        << SelectManager::distinctUnion(select1, select2).toSql()
        << QStringLiteral("SELECT posts.column1 FROM posts WHERE posts.column1 = 1"
                          " UNION "
                          "SELECT posts.column2 FROM posts WHERE posts.column2 = 2");

    QTest::newRow("union all")
        << SelectManager::unionAll(select1, select2).toSql()
        << QStringLiteral("SELECT posts.column1 FROM posts WHERE posts.column1 = 1"
                          " UNION ALL "
                          "SELECT posts.column2 FROM posts WHERE posts.column2 = 2");

    QTest::newRow("intersect")
        << SelectManager::intersect(select1, select2).toSql()
        << QStringLiteral("SELECT posts.column1 FROM posts WHERE posts.column1 = 1"
                          " INTERSECT "
                          "SELECT posts.column2 FROM posts WHERE posts.column2 = 2");

    QTest::newRow("except")
        << SelectManager::except(select1, select2).toSql()
        << QStringLiteral("SELECT posts.column1 FROM posts WHERE posts.column1 = 1"
                          " EXCEPT "
                          "SELECT posts.column2 FROM posts WHERE posts.column2 = 2");


    {
        const auto select1 = posts.select(column1).where(column1 == 1);
        const auto select2 = posts.select(column2).where(column2 == 2);
        const auto select3 = posts.select(column3).where(column3 == 3);

        QTest::newRow("")
            << SelectManager::distinctUnion(select1, select2).intersect(select3).toSql()
            << QStringLiteral("SELECT posts.column1 FROM posts WHERE posts.column1 = 1"
                              " UNION "
                              "SELECT posts.column2 FROM posts WHERE posts.column2 = 2"
                              " INTERSECT "
                              "SELECT posts.column3 FROM posts WHERE posts.column3 = 3");
    }

    {
        const auto select1 = posts.select(column1).where(column1 == 1)
                                 .take(1).skip(1).order(column1.ascending());
        const auto select2 = users.select(column4).where(column4 == 2)
                                 .take(2).skip(2).order(column4.descending());

        QTest::newRow("")
            << SelectManager::distinctUnion(select1, select2).toSql()
            << QStringLiteral("SELECT posts.column1 FROM posts WHERE posts.column1 = 1"
                              " UNION "
                              "SELECT users.column4 FROM users WHERE users.column4 = 2"
                              " ORDER BY posts.column1 ASC, users.column4 DESC"
                              " LIMIT 1 OFFSET 1");
    }
}

void ArielTest::insert()
{
    QFETCH(QString, sql);
    QFETCH(QString, result);
    QCOMPARE(sql, result);
}

void ArielTest::insert_data()
{
    QTest::addColumn<QString>("sql");
    QTest::addColumn<QString>("result");

    QTest::newRow("insert ints")
        << posts
            .insert(column1, 1)
            .insert(column2, 2)
            .toSql()
        << QStringLiteral("INSERT INTO posts (column1, column2) VALUES (1, 2)");

    QTest::newRow("insert values")
        << posts
            .insert(column1, 1)
            .insert(column2, "value")
            .toSql()
        << QStringLiteral("INSERT INTO posts (column1, column2) VALUES (1, 'value')");

    {
        InsertManager im;
        QTest::newRow("insert values without relation")
            << im.insert(column1, 1)
                 .insert(column2, "value")
                .toSql()
            << QStringLiteral("INSERT INTO posts (column1, column2) VALUES (1, 'value')");
    }

    {
        InsertManager im(posts);
        QTest::newRow("insert into select")
            << im.column(column1).select(posts.select(column1).where(column1 == 1)).toSql()
            << QStringLiteral("INSERT INTO posts (column1)"
                              " SELECT posts.column1 FROM posts"
                              " WHERE posts.column1 = 1");
    }
}

void ArielTest::update()
{
    QFETCH(QString, sql);
    QFETCH(QString, result);
    QCOMPARE(sql, result);
}

void ArielTest::update_data()
{
    QTest::addColumn<QString>("sql");
    QTest::addColumn<QString>("result");

    UpdateManager um;

    QTest::newRow("update")
        << um.table(posts)
            .set(column1, 1)
            .set(column2, 2)
            .where(column1 == 1)
            .order(column2.ascending())
            .take(2)
            .toSql()
        << QStringLiteral("UPDATE posts SET column1 = 1, column2 = 2"
                          " WHERE posts.column1 = 1"
                          " ORDER BY posts.column2 ASC LIMIT 2");
}

void ArielTest::deleteStatement()
{
    QFETCH(QString, sql);
    QFETCH(QString, result);
    QCOMPARE(sql, result);
}

void ArielTest::deleteStatement_data()
{
    QTest::addColumn<QString>("sql");
    QTest::addColumn<QString>("result");

    DeleteManager dm;

    QTest::newRow("delete")
        << dm.from(posts)
               .where(column1 == 1)
               .take(2)
               .toSql()
        << QStringLiteral("DELETE FROM posts WHERE posts.column1 = 1 LIMIT 2");
}

void ArielTest::sqlite()
{
    auto db = QSqlDatabase::addDatabase("QSQLITE", ":memory:");
    QCOMPARE(posts
                 .select(Ariel::Star)
                 .where(column1 == true && column2 == false)
                 .toSql(db),
             QStringLiteral("SELECT \"posts\".* FROM posts"
                            " WHERE \"posts\".\"column1\" = 1 AND \"posts\".\"column2\" = 0"));
}

void ArielTest::bindings()
{
    const auto manager = posts.select(Ariel::Star).where(column1 == BindValue("hello"));
    QCOMPARE(manager.toString(),
             QString("SELECT posts.* FROM posts WHERE posts.column1 = 'hello'"));
    QCOMPARE(manager.toSql(),
             QString("SELECT posts.* FROM posts WHERE posts.column1 = ?"));

    {
        InsertManager im;
        im.into(posts);
        im.insert(column1, BindValue(1));
        im.insert(column2, BindValue("Hello"));
        const auto collector = im.build();
        QCOMPARE(collector.value(),
                 QString("INSERT INTO posts (column1, column2) VALUES (?, ?)"));
        const QVariantList binds = collector.boundValues();
        QCOMPARE(binds.size(), 2);
        QCOMPARE(binds.at(0), QVariant(1));
        QCOMPARE(binds.at(1), QVariant("Hello"));
    }
}

QTEST_MAIN(ArielTest);

#include "tst_ariel.moc"
