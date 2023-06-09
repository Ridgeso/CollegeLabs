#ifndef __ChartClass__
#define __ChartClass__

#include <memory>
#include "ConfigClass.h"
struct Vector;
struct Matrix;

class ChartClass
{
private:
    std::shared_ptr<ConfigClass> cfg;
    int x_step;         // liczba odcinkow z jakich bedzie sie skladal wykres
    double x_min,x_max; // zakres zmiennej x
    double y_min,y_max; // zakres wartosci przyjmowanych przez funkcje
    double GetFunctionValue(double x); // zwraca wartosci rysowanej funkcji
    void ClipLine(const wxRect& boundaries, Vector& p1, Vector& p2);

public:
    ChartClass(std::shared_ptr<ConfigClass> c);
    void Set_Range();   // ustala wartosci zmiennych x_min,y_min,x_max,y_max
    double Get_Y_min(); // zwraca y_min
    double Get_Y_max(); // zwraca y_max
    void Draw(wxDC *dc, int w, int h);  // rysuje wykres
};

#endif
