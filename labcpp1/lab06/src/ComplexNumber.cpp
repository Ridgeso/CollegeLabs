#include <iostream>
#include "ComplexNumber.h"

ComplexNumber::ComplexNumber()
    : m_x(), m_y()
{

}

ComplexNumber::ComplexNumber(double x, double y)
    : m_x(x), m_y(y)
{

}

ComplexNumber::ComplexNumber(const ComplexNumber& complex)
    : m_x(complex.m_x), m_y(complex.m_y)
{

}

ComplexNumber::~ComplexNumber()
{

}

void ComplexNumber::Print() const
{
    if (m_x == 0.0 && m_y == 0.0)
        return;
    std::cout << "(" << m_x << ", " << m_y << ")";
}