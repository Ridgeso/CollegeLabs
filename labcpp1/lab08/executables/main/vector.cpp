#include"Vector.h"
#include"ComplexNumber.h"
#include <iostream>

#if I_AM_LAZY
    #define M Math::
#else
    #define M
    using namespace Math;
#endif

int main ()
{
    ComplexNumber liczba (1.2, 0.0);
    liczba.Print();
    std::cout<<"\n";
    
    M Vector pierwszy;
    pierwszy.SetY(1.1, 2.1).SetZ(1.3, 2.3);
    pierwszy.Print();

    double modul_1 = ComplexNumber::Abs(pierwszy.X());
    std::cout << "Moduł 1: "<< modul_1 << "\n";
    double modul_2 = static_cast<double>(pierwszy.X());
    std::cout << "Moduł 2: "<< modul_2 << "\n";

    M Vector drugi = 1.; // konwersja niejawna
    drugi.Print();

}