#ifndef SQLITEVISITOR_H
#define SQLITEVISITOR_H

#include "sqlvisitor.h"

namespace Ariel {

class SqliteVisitor : public SqlVisitor
{
private:
    void visit(const True &, AbstractCollector &collector) override
    {
        collector << "1";
    }

    void visit(const False &, AbstractCollector &collector) override
    {
        collector << "0";
    }
};

} // namespace Ariel

#endif // SQLITEVISITOR_H