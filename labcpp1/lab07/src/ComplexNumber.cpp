#include <iostream>
#include <cmath>
#include "ComplexNumber.h"

ComplexNumber::ComplexNumber()
    : m_x(), m_y()
{

}

ComplexNumber::ComplexNumber(double x, double y)
    : m_x(x), m_y(y)
{

}

ComplexNumber::~ComplexNumber()
{

}

double ComplexNumber::Abs(const ComplexNumber& complex)
{
    return std::sqrt(complex.m_x * complex.m_x + complex.m_y * complex.m_y);
}

ComplexNumber::operator double()
{
    return Abs(*this);
}

void ComplexNumber::Print() const
{
    std::cout << "(" << m_x << ", " << m_y << ")";
}