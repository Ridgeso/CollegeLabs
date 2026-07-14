#pragma once

#include <iostream>

class Ksztalt
{
public:
    //
    // Metoda bazowa wypisujaca do os
    //
    virtual std::ostream& wypisz(std::ostream& os) const = 0;

    //
    // Metoda bazowa zwracajaca pole powierzchni
    //
    virtual float polePow() const = 0;
private:
};

void wypisz(const Ksztalt& kszt);