// Prosze dopisac kod, dodac nowe pliki, tak aby program wykonywal
// sie, a wynik jego dzialania byl taki sam jak podany na końcu tego
// pliku.

// Prosze zaimplementowac klasy ComplexNumber i Vector. 
// ComplexNumber jest to para liczb, wypisywana w nawiasie
// okraglym. Vector natomiast jest to uporządkowany zbior trzech
// ComplexNumber. Klasy te obłsugują odpowiednie kowersje między typami.
// Uwaga: rozwiązanie nie może zawierać static_cast<>
// Uwaga: linia 44 powoduje błąd który pod odkomentowaniu powinien być odtworzonny

// Pliku Main.cpp, nie wolno modyfikowac.

// Ostateczny program powinien byc przyjazny dla programisty (miec
// czytelny i dobrze napisany kod), oraz powinna być spełniona zasada
// D.R.Y. - Don't Repeat Yourself.

// Przy wykonaniu zadania nie wolno korzystac z internetu, notatek,
// ani zadnych innych materialow.

// Kody źródłowe muszą znajdować się w katalogu do którego nikt oprócz
// właściciela nie ma praw dostępu.
// Rozwiazanie (czyli dodane pliki i Main.cpp należy wgrać do UPEL 
// jako archiwum tar.gz
// UWAGA:
// * archiwum powinno zawierać katalog z zadaniem, np. lab07/
// * archiwum nie powinno zawierać katalogu build/

#include"Vector.h"
#include"ComplexNumber.h"
#include <iostream>

int main ()
{
  ComplexNumber liczba (1.2, 0.0);
  liczba.Print();
  std::cout<<"\n";
  
  Vector pierwszy;
  pierwszy.SetY(1.1, 2.1).SetZ(1.3, 2.3);
  pierwszy.Print();
  // zmiana pierwszej wspolrzednej
  pierwszy.SetX(liczba);
  pierwszy.Print();

  // double modul_err = pierwszy.X(); // error: cannot convert ‘ComplexNumber’ to ‘double’ in initialization
  double modul_1 = ComplexNumber::Abs(pierwszy.X());
  std::cout << "Moduł 1: "<< modul_1 << "\n";
  double modul_2 = static_cast<double>(pierwszy.X());
  std::cout << "Moduł 2: "<< modul_2 << "\n";

  Vector drugi = 1.; // konwersja niejawna
  drugi.Print();

}
/* wynik dzialania programu:
(1.2, 0)
[(0, 0), (1.1, 2.1), (1.3, 2.3)]
[(1.2, 0), (1.1, 2.1), (1.3, 2.3)]
Moduł 1: 1.2
Moduł 2: 1.2
[(1, 1), (1, 1), (1, 1)]
*/
