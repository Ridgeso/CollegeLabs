#pragma once

#include <iostream>
#include <stdlib.h>

class MapPoint
{
public:
    
    void set_latitude(double latitude);
    
    void set_longitude(double longitude);

    void set_coordinates(double latitude, double longitude);
    
    MapPoint distanceMP(const MapPoint& dest);
    
    double distanceVal(const MapPoint& dest) const;

    void print() const;

private:
    
    double m_latitude = 0.0, m_longitude = 0.0;
};
