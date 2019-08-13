#ifndef TABLE_P_H
#define TABLE_P_H

#include <QString>
#include <QSharedDataPointer>

namespace Ariel {

class TableData : public QSharedData
{
public:
    using Pointer = QExplicitlySharedDataPointer<TableData>;

    bool operator ==(const TableData &other) const
    {
        return name == other.name;
    }

    QString name;
};


} // namespace Ariel

#endif // TABLE_P_H
