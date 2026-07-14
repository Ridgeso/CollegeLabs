#pragma once
#include <vector>

#include "Vehicle.h"


class Factory
{
public:

    //
    // Default constructor
    //
    Factory();

    Vehicle* operator++();

    //
    // Creates another Object of TestOjb
    //
    static Vehicle* produce();

    //
    // Set new pattern for function produce
    //
    static void prototype(const Vehicle& newPatern);

    //
    // clear all Vehicle allocated on the heap
    //
    static void erase();

private:
    int m_VehiclePointer;

    static std::vector<Vehicle*> s_VehicleList;
    static Vehicle* s_pattern;
};