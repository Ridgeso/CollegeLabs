#include <sstream>
#include "Sofa.h"


Sofa::Sofa(int width, int height, int deepth, int sitWidth)
    : Mebel(width, height, deepth), m_SitWidth(sitWidth)
{

}

Sofa::~Sofa()
{
    std::cout << "~Sofa" << std::endl;
}

std::string Sofa::Print() const
{
    std::stringstream ss;
    ss << "Sofa: sz: " << m_Width << " wys: " << m_Height << " dl: " << m_Deepth << " siedzisko: " << m_SitWidth;
    return ss.str();
}
