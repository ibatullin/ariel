#ifndef NODE_H
#define NODE_H

#include "abstractnode.h"
#include "../visitors/abstractvisitor.h"

namespace Ariel {

template<typename T>
class Node : public AbstractNode,
             public NodeMethods<T>
{
public:
    void accept(AbstractVisitor &visitor, AbstractCollector &collector) override
    {
        visitor.visit(*static_cast<T *>(this), collector);
    }

    AbstractNode *clone() const override
    {
        return new T(*static_cast<const T *>(this));
    }
};

} // namespace Ariel

#endif // NODE_H
