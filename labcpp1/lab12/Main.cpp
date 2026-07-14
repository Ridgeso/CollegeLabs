// Prosze dopisac kod, dodac nowe pliki, tak aby program wykonywal
// sie, a wynik jego dzialania byl taki sam jak podany na końcu tego
// pliku.

// Prosze napisac klase Vehicle, ktora ma "glosne" (tzn. wypisujace
// tekst) konstruktory i destruktor. Dodatkowo ta klasa ma nazwę.

// Prosze napisac klasę Factory, ktora tworzy obiekty typu Vehicle na
// podstawie zadanego wzorca. Jeżeli nie zostanie ustawiony żaden
// wzorzec, to tworzone sa obiekty przy użyciu domyślnego
// konstrutora. Od chwili gdy jest ustawiony jakiś wzorzec, tworzone
// sa kopie obiektu wzorcowego.
// Dodatkowo, dla klasy Vehicle należy zdefiniować przeciążenie operatora
// << na standardowe wyjście, tj. std::ostream.

// Prosze zadbac o dobre zarzadzanie pamiecia.
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
// * archiwum powinno zawierać katalog z zadaniem, np. lab12/
// * archiwum nie powinno zawierać katalogu build/


#include <iostream>
#include "Vehicle.h"
#include "Factory.h"

int main() {
  { // test funkcjonalnosci kl. Vehicle
    delete new Vehicle();
    delete new Vehicle("Vehicle");
    Vehicle never("mind");
    delete new Vehicle(never);
  }
  std::cout << "Factory:"<<std::endl;
    
  Vehicle *test(nullptr);
  test = Factory::produce();
  std::cout << "1: " << *test << std::endl;
  Factory factory; 
  test = factory.produce();
  std::cout << "2: " << test << std::endl;
  {
    Vehicle newPrototype("BMW");    
    factory.prototype(newPrototype);
  }
  test = factory.produce();
  std::cout << "3: " << test << std::endl;
  test = ++factory;
  std::cout << "4: " << test << std::endl;
  std::cout << "Clear memory" << std::endl;
  factory.erase();
}
/* wynik:
Vehicle::Vehicle()
~Vehicle(): default
Vehicle::Vehicle("Vehicle")
~Vehicle(): Vehicle
Vehicle::Vehicle("mind")
Vehicle::Vehicle(Vehicle("mind"))
~Vehicle(): mind
~Vehicle(): mind
Factory:
Vehicle::Vehicle()
1: default
Vehicle::Vehicle()
2: default
Vehicle::Vehicle("BMW")
Vehicle::Vehicle(Vehicle("BMW"))
~Vehicle(): BMW
Vehicle::Vehicle(Vehicle("BMW"))
3: BMW
Vehicle::Vehicle(Vehicle("BMW"))
4: BMW
Clear memory
~Vehicle(): default
~Vehicle(): default
~Vehicle(): BMW
~Vehicle(): BMW
~Vehicle(): BM
*/
