#pragma once
#include <string>
#include "MapPoint.h"

class MapDistance
{
public:
    //
    // inicjalizacja za pomoca nazwy polaczenia oraz obiektami reprezentujacymi te poczaczenia
    //
    MapDistance(const std::string& conection, const MapPoint& startPosition, const MapPoint& endPosition);

    //
    // wypisuje odleglosci miedzy punktami
    //
    void print() const;

    //
    // Zwraca dystanc miedzy punktami
    //
    double dist() const;

private:
    std::string m_conectionName;

    MapPoint m_pointDistance;
};