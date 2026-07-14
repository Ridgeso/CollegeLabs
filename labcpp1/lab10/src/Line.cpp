#include "Line.h"


Line::Line()
    : a(1), b(1)
{
}

Line::Line(double k)
    : a(k), b(k)
{
}

double Line::operator()(double x) const
{
    return a * x + b;
}

double Line::X0() const
{
    return - b / a;
}

void LPrint::operator()(const Line& eq) const
{
    std::cout << " y = " << eq.a << "* x + " << eq.b << "\tx0 = " << eq.X0() << std::endl;
}

void LPrint::operator()(const LArray& eqs) const
{
    for (int i = 0; i < eqs.eqsCapasity; i++)
    {
        std::cout << "[" << i << "] ";
        (*this)(eqs.eqs[i]);
    }
}

LArray::LArray(int n)
    : eqsCount(0), eqsCapasity(n), eqs(new Line[n])
{
}

LArray::~LArray()
{
    delete[] eqs;
}

LArray& LArray::Add(const Line& eq)
{
    eqs[eqsCount] = eq;
    eqsCount++;

    return *this;
}
