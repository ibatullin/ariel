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

    void setOrder(const AbstractOrder::Pointer &order);
    void addOrder(const AbstractOrder::Pointer &order);
    QList<AbstractOrder::Pointer> orders() const;
    void setLimit(const Limit::Pointer &limit);
    Limit::Pointer limit() const;
    void setOffset(const Offset::Pointer &offset);
    Offset::Pointer offset() const;
    void merge(const SelectStatement::Pointer &other);
    NodePointer root() const;
    SelectCore::Pointer context() const;

    void distinctUnion(const SelectCore::Pointer &core);
    void unionAll(const SelectCore::Pointer &core);
    void intersect(const SelectCore::Pointer &core);
    void except(const SelectCore::Pointer &core);

    static SelectStatement distinctUnion(const SelectCore::Pointer &lhs, const SelectCore::Pointer &rhs);
    static SelectStatement unionAll(const SelectCore::Pointer &lhs, const SelectCore::Pointer &rhs);
    static SelectStatement intersect(const SelectCore::Pointer &lhs, const SelectCore::Pointer &rhs);
    static SelectStatement except(const SelectCore::Pointer &lhs, const SelectCore::Pointer &rhs);

    using Node<SelectStatement>::create;

private:
    void addCore(const SelectCore::Pointer &core, const AbstractCompoundOperator::Pointer &compoundOperator);

    template<typename T>
    typename std::enable_if<std::is_base_of<AbstractCompoundOperator, T>::value, void>::type
    addCore(const SelectCore::Pointer &core)
    {
        auto compoundOperator = T::create(m_context, core);
        addCore(core, compoundOperator);
    }

    template<typename T>
    static typename std::enable_if<std::is_base_of<AbstractCompoundOperator, T>::value, SelectStatement>::type
    create(const SelectCore::Pointer &core1, const SelectCore::Pointer &core2)
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
