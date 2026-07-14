#pragma once

#include <string>


class Vehicle
{
public:
    
    //
    // default constructors and destructors
    //
    Vehicle();
    Vehicle(const std::string& name);
    Vehicle(const Vehicle& obj);
    
    ~Vehicle();

    //
    // Getter for m_Name
    //
    const std::string& name() const;

private:
    std::string m_Name;
};

std::ostream& operator<<(std::ostream& os, const Vehicle& v);
std::ostream& operator<<(std::ostream& os, const Vehicle* v);