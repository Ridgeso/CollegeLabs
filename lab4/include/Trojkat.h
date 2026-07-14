#pragma once

#include "Ksztalt.h"


class Trojkat : public Ksztalt
{
public:
    //
    //  domyslny konstruktor
    //
    Trojkat(float a, float b, float c);
    
    //
    // metoda wypisujaca trojkat do 'os' nadpisywana z klasy dziedziczonej
    //
    std::ostream& wypisz(std::ostream& os) const override;

    //
    // metoda zwracajaca pole powierzchni trojkata z klasy dziedziczonej
    //
    float polePow() const override;

private:
    float m_A, m_B, m_C;
};
