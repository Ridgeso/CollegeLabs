#pragma once
#include <iostream>

class LPrint;
class LArray;

class Line
{
public:
    //
    // Default constructors
    //
    Line();
    Line(double k);

    //
    // Operator calculating Line equasion
    //
    double operator()(double x) const;

    //
    // Function returning position of point zero on y axis
    //
    double X0() const;

    friend LPrint;
private:
    // values of : y = "a" * x + "b"
    double a;
    double b;
};

class LPrint
{
public:
    //
    // Operator printing formated Line
    //
    void operator()(const Line& eq) const;

    //
    // Operator printing formated Line holded by LArray
    //
    void operator()(const LArray& eqs) const;

private:

};

class LArray
{
public:
    //
    // Default constructors
    //
    LArray(int n);
    ~LArray();

    //
    // Inserting Line to collection of Lines
    //
    LArray& Add(const Line& eq);

    friend LPrint;
private:
    int eqsCount;       // Curent Count of lines
    int eqsCapasity;    // Max Count of Lines
    Line* eqs;          // Lines collection
};
