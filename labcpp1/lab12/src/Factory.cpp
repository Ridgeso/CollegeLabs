#include "Factory.h"
#include <iostream>


std::vector<Vehicle*> Factory::s_VehicleList = {};
Vehicle* Factory::s_pattern = nullptr;

Factory::Factory()
    : m_VehiclePointer(0)
{ }

Vehicle* Factory::operator++()
{
    return produce();
}

Vehicle* Factory::produce()
{
    Vehicle* newVehicle;

    newVehicle = s_pattern ? new Vehicle(*s_pattern) : new Vehicle();

    s_VehicleList.push_back(newVehicle);
    return newVehicle;
}

void Factory::prototype(const Vehicle& newPatern)
{
    if (s_pattern != nullptr)
        delete s_pattern;
    
    s_pattern = new Vehicle(newPatern);
}

void Factory::erase()
{
    for (Vehicle* Vehicle : s_VehicleList)
        delete Vehicle;

    delete s_pattern;
}
