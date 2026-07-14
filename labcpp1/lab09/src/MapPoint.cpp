#include "MapPoint.h"

#include <iostream>

namespace MTH {

    Point::Point(double x, double y)
        : m_X(x), m_Y(y)
    {
    }

    Point::~Point()
    {
    }

    Point& Point::operator=(const Point& other)
    {
        if (this == &other)
        {
            std::cout << "[MTH::Warning] Discarding self-assignment" << std::endl;
            return *this;
        }

        m_X = other.m_X;
        m_Y = other.m_Y;

        return *this;
    }

    void Print(const Point& point)
    {
        std::cout << "[MTH::Point] X=" << point.m_X << " Y=" << point.m_Y << std::endl;
    }

}

namespace MP {

    Point::Point(const std::string& name, double Lattitude, double Longitute)
        : m_Name(name), m_Lattitude(Lattitude), m_Longitute(Longitute)
    {
    }

    Point::Point(const std::string& name, const ::MTH::Point& point)
        : m_Name(name), m_Lattitude(point.m_X), m_Longitute(point.m_Y)
    {
    }

    Point::~Point()
    {
    }

    Point::operator MTH::Point() const
    {
        return MTH::Point(m_Lattitude, m_Longitute);
    }
    
    void Print(const Point& point)
    {
        std::cout <<"[MP::Point] " << point.m_Name << ": Lattitude=" << point.m_Lattitude << " Longitute=" << point.m_Longitute << std::endl;
    }

}