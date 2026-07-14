#include <algorithm>
#include "ListaWektorow.h"


void ListaWektorow::Dodaj(Wektor2D* wek)
{
    m_Wectors.push_back(wek);
}

void ListaWektorow::Wypisz() const
{
    std::for_each(m_Wectors.begin(), m_Wectors.end(), [](Wektor2D* wek)
    {
        wek->Wypisz();
    });
}

void ListaWektorow::PosortujWedlugX()
{
    std::cout << "Posortowana wedlug wsprzednych X" << std::endl;

    std::sort(m_Wectors.begin(), m_Wectors.end(), [](Wektor2D* w1, Wektor2D* w2)
    {
        return w1->GetX() < w2->GetX();
    });
}

void ListaWektorow::PosortujWedlugY()
{
    std::cout << "Posortowana wedlug wsprzednych Y" << std::endl;

    std::sort(m_Wectors.begin(), m_Wectors.end(), [](Wektor2D* w1, Wektor2D* w2)
    {
        return w1->GetY() < w2->GetY();
    });
}