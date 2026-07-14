#pragma once

#include "Visitor.h"

class AccumulatingVisitor : public Visitor
{
public:
    AccumulatingVisitor()
        : m_TotalSum(0.f)
    { }

    void visit(const IntData* data) override;
    void visit(const FloatData* data) override;
    
    float getTotalSum() const;

private:
    float m_TotalSum;
};