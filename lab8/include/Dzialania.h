#pragma once
#include "Wektor2D.h"

class DzialaniaNaZbiorach
{
public:
    DzialaniaNaZbiorach(std::set<Wektor2D>& zbior);

    void WypiszXWiekszeOd(int val) const;
    void ZamienX(int X, int nX);

private:
    std::set<Wektor2D> m_Zbior;
};