#include <sstream>
#include "Lozko.h"

Lozko::Lozko(int width, int height, int deepth, int sleepWidth)
    : Mebel(width, height, deepth), m_SleepWidth(sleepWidth)
{

}

Lozko::~Lozko()
{
    std::cout << "~Lozko" << std::endl;
}

std::string Lozko::Print() const
{
    std::stringstream ss;
    ss << "Lozko: sz: " << m_Width << " wys: " << m_Height << " dl: " << m_Deepth << " sz.spania: " << m_SleepWidth;
    return ss.str();
}
