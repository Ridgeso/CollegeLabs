#include <sstream>
#include "Mebel.h"


Mebel::Mebel(int width, int height, int deepth)
    : m_Width(width), m_Height(height), m_Deepth(deepth)
{

}

std::string Mebel::Print() const
{
    std::stringstream ss;
    ss << "Mebel: sz: " << m_Width << " wys: " << m_Height << " dl: " << m_Deepth;
    return ss.str();
}

Mebel::~Mebel()
{
    std::cout << "~Mebel" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Mebel& mebel)
{
    return os << mebel.Print();
}
