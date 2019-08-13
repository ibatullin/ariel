#ifndef TABLENODE_H
#define TABLENODE_H

#include "node.h"
#include "../table_p.h"

namespace Ariel {


class TableNode : public Node<TableNode>
{
public:
    TableNode();
    explicit TableNode(TableData::Pointer d);
    TableNode(const TableNode &other);
    TableNode &operator =(TableNode other);
    QString name() const;
    TableData::Pointer data() const;

private:
    TableData::Pointer d;
};

} // namespace Ariel

#endif // TABLENODE_H
