#include <iostream>

#include "Vehicle.h"


Vehicle::Vehicle()
    : m_Name("default")
{
    std::cout << "Vehicle::Vehicle()" << std::endl;
}

Vehicle::Vehicle(const std::string& name)
    : m_Name(name)
{
    std::cout << "Vehicle::Vehicle(\"" << m_Name << "\")" << std::endl;
}

Vehicle::Vehicle(const Vehicle& obj)
    : m_Name(obj.m_Name)
{
    std::cout << "Vehicle::Vehicle(Vehicle(\"" << m_Name << "\"))" << std::endl;
}

Vehicle::~Vehicle()
{
    std::cout << "~Vehicle(): ";
    
    if (m_Name == "")
        std::cout << "default";
    else
        std::cout << m_Name;

    std::cout << std::endl;
}

const std::string& Vehicle::name() const
{
    return m_Name;
}

std::ostream& operator<<(std::ostream& os, const Vehicle& v)
{
    os << v.name();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Vehicle* v)
{
    os << v->name();
    return os;
}
