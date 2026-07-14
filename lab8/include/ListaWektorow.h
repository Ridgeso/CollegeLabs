#pragma once

#include <iostream>
#include <vector>
#include "Wektor2D.h"

class ListaWektorow
{
public:
    void Dodaj(Wektor2D* wek);
    void Wypisz() const;
    void PosortujWedlugX();
    void PosortujWedlugY();

private:
    std::vector<Wektor2D*> m_Wectors;
};