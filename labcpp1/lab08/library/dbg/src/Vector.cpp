#include <iostream>

#include "Vector.h"

namespace Math
{

    Vector::Vector()
    {
        for (int i = 0; i < m_numOfNumbers; ++i)
        {
            m_numbers[i] = ComplexNumber();
        }
    }

    Vector::Vector(double value)
    {
        for (int i = 0; i < m_numOfNumbers; ++i)
        {
            m_numbers[i] = ComplexNumber(value, value);
        }
    }

    Vector::~Vector()
    {
    #if DEBUG
        std::cout << "Vector Destroyed" << std::endl;
    #endif
    }

    ComplexNumber& Vector::X()
    {
        return m_numbers[0];
    }

    Vector& Vector::SetY(double x, double y)
    {
        m_numbers[1] = ComplexNumber(x, y);
        return *this;
    }

    Vector& Vector::SetZ(double x, double y)
    {
        m_numbers[2] = ComplexNumber(x, y);
        return *this;
    }

    Vector& Vector::SetX(const ComplexNumber& x)
    {
        m_numbers[0] = x;
        return *this;
    }

    void Vector::Print() const
    {
        std::cout << "[";
        for (int i = 0; i < m_numOfNumbers - 1; ++i)
        {
            m_numbers[i].Print();
            std::cout << ", ";
        }
        m_numbers[m_numOfNumbers - 1].Print();
        std::cout << "]" << std::endl;
    }

}