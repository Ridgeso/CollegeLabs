#include <iostream>
#include "PrintingVisitor.h"
#include "Data.h"


void PrintingVisitor::visit(const IntData* data) const
{
    std::cout << data->get() << " ";
}

void PrintingVisitor::visit(const FloatData* data) const
{
    std::cout << data->getValue() << " ";
}