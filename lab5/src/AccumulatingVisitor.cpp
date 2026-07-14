#include "AccumulatingVisitor.h"
#include "Data.h"


void AccumulatingVisitor::visit(const IntData* data)
{
    m_TotalSum += (float)data->get();
}

void AccumulatingVisitor::visit(const FloatData* data)
{
    m_TotalSum += data->getValue();
}

float AccumulatingVisitor::getTotalSum() const
{
    return m_TotalSum;
}
