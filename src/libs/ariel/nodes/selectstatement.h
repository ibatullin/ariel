#ifndef SELECTSTATEMENT_H
#define SELECTSTATEMENT_H

#include "node.h"

#include "order.h"
#include "selectcore.h"
#include "compoundoperators.h"

#include <utility>

namespace Ariel {

class SelectStatement : public Node<SelectStatement>
{
public:
    SelectStatement();
    SelectStatement(const SelectStatement &other);
    SelectStatement &operator =(SelectStatement other);

    void setOrder(AbstractOrder::Pointer order);
    void addOrder(AbstractOrder::Pointer order);
    QList<AbstractOrder::Pointer> orders() const;
    void setLimit(Limit::Pointer limit);
    Limit::Pointer limit() const;
    void setOffset(Offset::Pointer offset);
    Offset::Pointer offset() const;
    void merge(SelectStatement::Pointer other);
    NodePointer root() const;
    SelectCore::Pointer context() const;

    void distinctUnion(SelectCore::Pointer core);
    void unionAll(SelectCore::Pointer core);
    void intersect(SelectCore::Pointer core);
    void except(SelectCore::Pointer core);

    static SelectStatement distinctUnion(SelectCore::Pointer lhs, SelectCore::Pointer rhs);
    static SelectStatement unionAll(SelectCore::Pointer lhs, SelectCore::Pointer rhs);
    static SelectStatement intersect(SelectCore::Pointer lhs, SelectCore::Pointer rhs);
    static SelectStatement except(SelectCore::Pointer lhs, SelectCore::Pointer rhs);

    using Node<SelectStatement>::create;

private:
    void addCore(SelectCore::Pointer core, AbstractCompoundOperator::Pointer compoundOperator);

    template<typename T>
    typename std::enable_if<std::is_base_of<AbstractCompoundOperator, T>::value, void>::type
    addCore(SelectCore::Pointer core)
    {
        auto compoundOperator = T::create(m_context, core);
        addCore(core, compoundOperator);
    }

    template<typename T>
    static typename std::enable_if<std::is_base_of<AbstractCompoundOperator, T>::value, SelectStatement>::type
    create(SelectCore::Pointer core1, SelectCore::Pointer core2)
    {
        SelectStatement s;
        s.m_operator = T::create(core1, core2);
        s.m_context = core2;
        s.m_root = s.m_operator;
        return s;
    }

    QList<AbstractOrder::Pointer> m_orders;
    Limit::Pointer m_limit;
    Offset::Pointer m_offset;
    NodePointer m_root;
    AbstractCompoundOperator::Pointer m_operator;
    SelectCore::Pointer m_context;

//    std::unique_ptr<Limit> ptr;
};

} // namespace Ariel


#endif // SELECTSTATEMENT_H
