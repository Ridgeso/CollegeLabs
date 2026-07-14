#pragma once

#include "Visitor.h"

class PrintingVisitor : public Visitor
{
public:
    void visit(const IntData* data) const override;
    void visit(const FloatData* data) const override;

private:

};