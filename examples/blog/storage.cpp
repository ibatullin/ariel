#include "storage.h"

#include <QDate>
#include <QtGlobal>

Storage::Storage()
{
}

Ariel::Table Storage::posts() const
{
  return Ariel::Table("posts");
}

Ariel::SelectManager Storage::allPosts() const
{
  return posts().select(Ariel::Star);
}

Ariel::SelectManager Storage::postsByDate(const QDate &date) const
{
    auto posts = this->posts();
    return allPosts()
        .where(posts["date"] == date)
        .order(posts["date"].ascending());
}

Ariel::SelectManager Storage::todayPosts() const
{
  return postsByDate(QDate::currentDate());
}

Ariel::SelectManager Storage::search(const QString &text) const
{
    auto posts = this->posts();
    return allPosts()
      .where(posts["title"] == "%" + text + "%"
             || posts["text"] == "%" + text + "%")
      .order(posts["date"].ascending());
}

void Storage::createDatabase()
{
    QSqlQuery query(
        "CREATE TABLE IF NOT EXISTS posts ("
        "title TEXT,"
        "text TEXT,"
        "date TEXT)");

    query.exec();

    auto posts = this->posts();
    auto insert = posts.insert(posts["title"], "Ariel")
                       .insert(posts["text"], "Hey")
                       .insert(posts["date"], QDate::currentDate());

    auto collector = insert.build();
    QSqlQuery insertQuery(collector.value());
    for (const QVariant &bindValue : collector.boundValues())
        insertQuery.addBindValue(bindValue);
}
