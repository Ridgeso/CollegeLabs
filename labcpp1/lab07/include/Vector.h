#pragma once

#include <iostream>
#include <array>
#include "ComplexNumber.h"

class Vector
{
public:
    //
    // Konstruktory
    //
    Vector();
    // Konstructor double
    Vector(double value);
    // Domyslny Destruktor
    ~Vector();

    //
    // zwracanie x,
    //
    ComplexNumber& X();

    //
    // nadaja wartosc x, y, z
    //
    Vector& SetY(double x, double y);
    Vector& SetZ(double x, double y);

    //
    // nadaja Kopiowanie x, y, z
    //
    Vector& SetX(const ComplexNumber& x);

    //
    // wypisuje Vector
    //
    void Print() const;

private:
    static const int m_numOfNumbers = 3;
    std::array<ComplexNumber, m_numOfNumbers> m_numbers;
};
