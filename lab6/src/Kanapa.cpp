#include <sstream>
#include "Kanapa.h"

Kanapa::Kanapa(int width, int height, int deepth, int sitWidth, int sleepWidth)
    : Sofa(width, height, deepth, sitWidth), Lozko(width, height, deepth, sleepWidth)
{

}

Kanapa::~Kanapa()
{
    std::cout << "~Kanapa" << std::endl;
}

std::string Kanapa::Print() const
{
    std::stringstream ss;
    // ss << Mebel::Print() << std::endl;
    ss << Sofa::Print() << std::endl;
    ss << Lozko::Print();
    return ss.str();
}