#include "abstractvisitor.h"

#include <QVariant>

#include <QSqlDriver>

namespace Ariel {

bool AbstractVisitor::visitNode(NodePointer node, AbstractCollector &collector)
{
    if (node) {
        node->accept(*this, collector);
        return true;
    } else {
        return false;
    }
}

void Ariel::AbstractVisitor::maybeVisit(Ariel::NodePointer node, AbstractCollector &collector)
{
    if (node) {
        collector << Delimeters::Space;
        visitNode(node, collector);
    }
}

} // namespace Ar
