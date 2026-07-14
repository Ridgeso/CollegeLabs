#pragma once

#include "Ksztalt.h"

class Kolo : public Ksztalt
{
public:
    //
    //  domyslny konstruktor
    //
    Kolo(float r);

    //
    // metoda wypisujaca kolo do 'os' nadpisywana z klasy dziedziczonej
    //
    std::ostream& wypisz(std::ostream& os) const override;

    //
    // metoda zwracajaca pole powierzchni kola z klasy dziedziczonej
    //
    float polePow() const override;

private:
    float m_R;
};
