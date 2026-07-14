#include "MapPoint.h"

#include <iostream>
#include <cmath>

void MapPoint::set_latitude(double latitude)
{
    m_latitude = latitude;
}

void MapPoint::set_longitude(double longitude)
{
    m_longitude = longitude;
}

void MapPoint::set_coordinates(double latitude, double longitude)
{
    m_latitude = latitude;
    m_longitude = longitude;
}

MapPoint MapPoint::distanceMP(const MapPoint& dest)
{
    MapPoint distance;

    distance.set_coordinates(
        dest.m_latitude - m_latitude,
        dest.m_longitude - m_longitude
    );
    
    return distance;
}

double MapPoint::distanceVal(const MapPoint& dest) const
{
    MapPoint distance(dest);

    return std::sqrt(distance.m_latitude * distance.m_latitude + distance.m_longitude * distance.m_longitude);
}

void MapPoint::print() const
{
    std::cout << "Point: " << m_latitude << " " << m_longitude << std::endl;
}

