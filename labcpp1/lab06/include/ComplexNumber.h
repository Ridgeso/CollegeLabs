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
    // kopiujac
    ComplexNumber(const ComplexNumber& complex);
    // destruktor
    ~ComplexNumber();

    //
    // Wypisuje liczbe
    //
    void Print() const;

private:
    double m_x = 0.0, m_y = 0.0;
};