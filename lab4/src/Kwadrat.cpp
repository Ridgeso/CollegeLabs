#include "Kwadrat.h"


Kwadrat::Kwadrat(float a)
    : m_A(a)
{ }

std::ostream& Kwadrat::wypisz(std::ostream& os) const
{
    os << "Kwadrat o boku: " << m_A << std::endl;    
    return os;
}

float Kwadrat::polePow() const
{
    return m_A * m_A;
}