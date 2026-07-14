#pragma once

#include <iostream>
#include <vector>
#include "ComplexNumber.h"

class Vector
{
public:
    //
    // Konstruktor
    //
    Vector();
    //
    // Domyslny konstruktor
    //
    Vector(const ComplexNumber& x, const ComplexNumber& y, const ComplexNumber& z);
    //
    // Konstruktor Przenoszacy
    //
    Vector(Vector&& v);
    //
    // Domyslny Destruktor
    //
    ~Vector();

    // nadaja wartosc x, y, z
    Vector* SetX(double x, double y);
    Vector* SetY(double x, double y);
    Vector* SetZ(double x, double y);

    // zwraca n-ta liczbe
    ComplexNumber& GetComponent(int n);
    const ComplexNumber& GetComponent(int n) const;

    static Vector* CreateConstVector(
        const ComplexNumber& x,
        const ComplexNumber& y,
        const ComplexNumber& z
    );

    //
    // wypisuje Vector
    //
    void Print() const;

    //
    // Czyszczenie Vectorow
    //
    static void Cleanup();

private:
    int m_numOfNumbers = 3;
    ComplexNumber* m_numbers;

    static std::vector<Vector*> s_newVectors;
};
