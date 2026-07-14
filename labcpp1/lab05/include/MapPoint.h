#pragma once

#include <iostream>
#include <stdlib.h>

class MapPoint
{
public:
    //
    // Podstawowe konstruktory
    //
    MapPoint();

    MapPoint(double latitude, double longitude);
    
    MapPoint(const MapPoint& point);
    
    ~MapPoint();
    
    //
    // ustanawia nowa wartosc dla `latitude`
    //
    void set_latitude(double latitude);
    
    //
    // ustanawia nowa wartosc dla `longitude`
    //
    void set_longitude(double longitude);

    //
    // ustanawia nowa wartosc dla `latitude` oraz `longitude`
    //
    void set_coordinates(double latitude, double longitude);
    
    //
    // zwraca nowy punkt o koordynatach rownych roznicy koordynatow miedzy `dest` a samym soba
    //
    MapPoint distanceMP(const MapPoint& dest);
    
    //
    // zwraca wartosc odleglosci miedzy `dest` a soba
    //
    double distanceVal(const MapPoint& dest) const;

    //
    // wypisuje odleglosci
    //
    void print() const;

    // 
    // zwraca ilosc utworznonych punktow
    //
    static int N_MAP_POINT(bool inc = false);

    friend class MapDistance;

private:
    
    double m_latitude = 0.0, m_longitude = 0.0;

};
