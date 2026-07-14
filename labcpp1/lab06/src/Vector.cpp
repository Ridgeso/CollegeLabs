#include <iostream>

#include "Vector.h"

std::vector<Vector*> Vector::s_newVectors = {};

Vector::Vector()
    : m_numbers(new ComplexNumber[m_numOfNumbers])
{
    m_numbers[0] = ComplexNumber();
    m_numbers[1] = ComplexNumber();
    m_numbers[2] = ComplexNumber();

    s_newVectors.push_back(this);
}

Vector::Vector(const ComplexNumber& x, const ComplexNumber& y, const ComplexNumber& z)
    : m_numbers(new ComplexNumber[m_numOfNumbers])
{
    
    m_numbers[0] = x;
    m_numbers[1] = y;
    m_numbers[2] = z;

    s_newVectors.push_back(this);
}

Vector::Vector(Vector&& v)
{
    m_numbers = v.m_numbers;
    m_numOfNumbers = v.m_numOfNumbers;

    v.m_numbers = nullptr;
    v.m_numOfNumbers = 0;
}

Vector::~Vector()
{
    delete[] m_numbers;
}

Vector* Vector::SetX(double x, double y)
{
    m_numbers[0] = ComplexNumber(x, y);
    return this;
}

Vector* Vector::SetY(double x, double y)
{
    m_numbers[1] = ComplexNumber(x, y);
    return this;
}

Vector* Vector::SetZ(double x, double y)
{
    m_numbers[2] = ComplexNumber(x, y);
    return this;
}

ComplexNumber& Vector::GetComponent(int n)
{
    return m_numbers[n];
}

const ComplexNumber& Vector::GetComponent(int n) const
{
    return m_numbers[n];
}

Vector* Vector::CreateConstVector(
    const ComplexNumber& x,
    const ComplexNumber& y,
    const ComplexNumber& z
)
{
    return new Vector(x, y, z);
}

void Vector::Print() const
{
    std::cout << "[";
    if (m_numOfNumbers != 0)
    {
        for (int i = 0; i < m_numOfNumbers - 1; ++i)
        {
            m_numbers[i].Print();
            std::cout << ", ";
        }
        m_numbers[m_numOfNumbers - 1].Print();
    }
    std::cout << "]" << std::endl;
}

void Vector::Cleanup()
{
    for (auto v : s_newVectors)
    {
        delete v;
    }
}