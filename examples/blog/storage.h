#ifndef STORAGE_H
#define STORAGE_H

#include "table.h"
#include "selectmanager.h"

class Storage
{
public:
    Storage();

    Ariel::Table posts() const;
    Ariel::SelectManager allPosts() const;
    Ariel::SelectManager postsByDate(const QDate &date) const;
    Ariel::SelectManager todayPosts() const;
    Ariel::SelectManager search(const QString &text) const;

    void createDatabase();
};

#endif // STORAGE_H
