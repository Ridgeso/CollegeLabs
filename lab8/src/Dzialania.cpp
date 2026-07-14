#include <algorithm>
#include <iostream>
#include "Dzialania.h"

DzialaniaNaZbiorach::DzialaniaNaZbiorach(std::set<Wektor2D>& zbior)
    : m_Zbior(std::move(zbior))
{ }


void DzialaniaNaZbiorach::WypiszXWiekszeOd(int val) const
{
    // auto it = m_Zbior.upper_bound(val);
    std::for_each(m_Zbior.upper_bound(val), m_Zbior.end(), [](const Wektor2D& wek)
    {
        wek.Wypisz();
    });
}

void DzialaniaNaZbiorach::ZamienX(int X, int nX)
{
    // auto it = m_Zbior.find(X);
    // Wektor2D tmp = Wektor2D((*it).GetName(), nX, (*it).GetY());
    // // m_Zbior.extract(it);
    // m_Zbior.insert(tmp);
}
