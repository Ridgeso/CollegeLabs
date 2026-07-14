#include <iostream>
#include "Wektor2D.h"

Wektor2D::Wektor2D(int X)
    : m_X(X)
{ }

Wektor2D::Wektor2D(const std::string& name, int X, int Y)
    : m_Name(name), m_X(X), m_Y(Y)
{ }

void Wektor2D::Wypisz() const
{
    std::cout << m_Name << " (" << m_X << ", " << m_Y << ")" << std::endl;
}
