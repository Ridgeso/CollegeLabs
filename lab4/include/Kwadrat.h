#pragma once

#include "Ksztalt.h"


class Kwadrat : public Ksztalt
{
public:
    //
    //  domyslny konstruktor
    //
    Kwadrat(float a);

    //
    // metoda wypisujaca kwadrat do 'os' nadpisywana z klasy dziedziczonej
    //
    std::ostream& wypisz(std::ostream& os) const override;

    //
    // metoda zwracajaca pole powierzchni kwadratu z klasy dziedziczonej
    //
    float polePow() const override;

private:
    float m_A;
};
