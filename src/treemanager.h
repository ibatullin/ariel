#ifndef TREEMANAGER_H
#define TREEMANAGER_H

#include "visitors/sqlvisitor.h"
#include "collectors/sqlcollector.h"

#include <QSqlQuery>

namespace Ariel {

class AbstractTreeManager
{
public:
    AbstractTreeManager() = default;
    virtual ~AbstractTreeManager() = default;

    SqlCollector build() const;
    SqlCollector build(const QSqlDatabase &db) const;
    void collect(AbstractCollector &collector) const;
    void collect(const QSqlDatabase &db, AbstractCollector &collector) const;
    void collect(AbstractVisitor *visitor, AbstractCollector &collector) const;

    QString toString() const;
    QString toSql() const;
    QString toSql(const QSqlDatabase &db) const;

protected:
    virtual void accept(AbstractVisitor *visitor, AbstractCollector &collector) const = 0;
};


template<typename T>
class TreeManager : public AbstractTreeManager
{
public:
    explicit TreeManager()
        : m_ast(T::create())
    {
    }

    explicit TreeManager(typename T::Pointer ast)
        : m_ast(ast)
    {
    }

    void setAst(typename T::Pointer ast)
    {
        m_ast = ast;
    }

    typename T::Pointer ast() const
    {
        return m_ast;
    }

    void accept(AbstractVisitor *visitor, AbstractCollector &collector) const override
    {
        visitor->visitNode(ast(), collector);
    }

    void detach()
    {
        m_ast.detach();
    }

private:
    typename T::Pointer m_ast;
};

} // namespace Ariel

QDebug operator<<(QDebug debug, const Ariel::AbstractTreeManager &manager);

#endif // TREEMANAGER_H
