#include "Trojkat.h"
#include <cmath>


Trojkat::Trojkat(float a, float b, float c)
    : m_A(a), m_B(b), m_C(c)
{ }

std::ostream& Trojkat::wypisz(std::ostream& os) const
{
    os << "Trojkat o bokach: " << m_A << " " << m_B << " " << m_C << std::endl;
    return os;
}

float Trojkat::polePow() const
{
    float x = (m_A + m_B + m_C) / 2.f;
    return std::sqrt( x * (x - m_A) * (x - m_A) * (x - m_A));
}
