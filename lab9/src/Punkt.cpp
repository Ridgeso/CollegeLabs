#include "Punkt.h"

Punkt::Punkt(const std::string& name, int x, int y)
    : m_Name(name), m_Wsp{x, y}
{ }

Punkt& Punkt::operator=(const Punkt& other)
{
    if (this != &other)
    {
        m_Wsp[0] = other.m_Wsp[0];
        m_Wsp[1] = other.m_Wsp[1];
    }
    return *this;
}


std::ostream& operator<<(std::ostream& os, const Punkt& p)
{
    os << p.m_Name << '(' << p.m_Wsp[0] << ',' << p.m_Wsp[1] << ')';
    return os;
}

bool Punkt::operator<(const Punkt& other) const
{
    return m_Wsp[0] == other.m_Wsp[0] ? m_Wsp[1] < other.m_Wsp[1] : m_Wsp[0] < other.m_Wsp[0];
}
