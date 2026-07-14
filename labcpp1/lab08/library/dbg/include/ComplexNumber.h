#pragma once

class ComplexNumber
{
public:
    //
    // inicjalizacja Objektu
    //
    ComplexNumber();
    // przy pomocy jego wartosci
    ComplexNumber(double x, double y);
    // destruktor
    ~ComplexNumber();

    //
    //  zwraca dlugosc Complex Number
    //
    static double Abs(const ComplexNumber& complex);

    // Operatoru
    explicit operator double();

    //
    // Wypisuje liczbe
    //
    void Print() const;

private:
    double m_x = 0.0, m_y = 0.0;
};