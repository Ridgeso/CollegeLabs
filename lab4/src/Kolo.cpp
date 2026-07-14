#include "Kolo.h"


Kolo::Kolo(float r)
    : m_R(r)
{ }

std::ostream& Kolo::wypisz(std::ostream& os) const
{
    os << "Kolo o promieniu: " << m_R << std::endl;
    return os;
}

float Kolo::polePow() const
{
    return m_R * m_R * 3.1415f; 
}