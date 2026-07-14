// Prosze dopisac kod, dodac nowe pliki, tak aby program wykonywal
// sie, a wynik jego dzialania byl taki sam jak podany na końcu tego
// pliku.

// Prosze napisac klasę MapPoint, ktora reprezentuje punkt na
// mapie skladajacy sie dlugosci (longitude) i szerokosci
// (latitude) geograficznej bez oznaczania polkol.
//
// Proszę napisć klasę MapDistance która zawiera jako składową MapPoint
// do przechowiania informacji o różnicy składowych latitude i longitude
// przekazanych do konstruktora dwóch punktów (MapPoint).
// Pierwszy argument konstruktora to nazwa (label) wykorzystana w funkcji print()
// Metoda mpdist.dist() zwraca moduł (sqrt) przechowywanego MapPoint

// Funkcja klasy MapPoint::N_MAP_POINT zwraca informacje o wszystkich 
// utworzonych punktach (każda nowa instancja klasy MapPoint inkrementuje odpowiednią zmienną, 
// która zwraca ta metoda).

// Pliku Main.cpp, nie wolno modyfikowac.

// Ostateczny program powinien byc przyjazny dla programisty (miec
// czytelny i dobrze napisany kod).

// Przy wykonaniu zadania nie wolno korzystac z internetu, notatek,
// ani zadnych innych materialow.

// Kody źródłowe muszą znajdować się w katalogu do którego nikt oprócz
// właściciela nie ma praw dostępu.
// Rozwiazanie (czyli dodane pliki i Main.cpp należy wgrać do UPEL 
// jako archiwum tar.gz
// UWAGA:
// * archiwum powinno zawierać katalog z zadaniem, np. lab05/
// * archiwum nie powinno zawierać katalogu build/

#include "MapPoint.h"
#include "MapDistance.h"

int main() {
  using std::cout;

  cout<<"========== KRK ==========\n";
  const MapPoint krk(19.9383,50.0613);    // # 1
  krk.print();

  cout<<"========== PORTO & Null Island ==========\n";
  MapPoint porto(41.1621, -8.6219); // # 2
  const MapPoint nullIsland;        // # 3
  porto.print();
  nullIsland.print();

  cout<<"========== MAP DISTANCE ==========\n";
  MapDistance md("PORTO-NULLISLAND",porto,nullIsland); // # 4
  md.print();
  cout<<"MapDistance : "<< md.dist() << std::endl;

  cout<<"========== COPY & STAT ==========\n";
  MapPoint cpyNullIsland(nullIsland);   // # 5
  cout<<"<N> MapPoints : "<< MapPoint::N_MAP_POINT() << std::endl;


  return 0;
}
/** Wynik dzialania programu:
========== KRK ==========
Point: (19.9383, 50.0613)
========== PORTO & Null Island ==========
Point: (41.1621, -8.6219)
Point: (0, 0)
========== MAP DISTANCE ==========
MapDistance [PORTO-NULLISLAND]: (-41.1621, 8.6219)
MapDistance : 42.0554
========== COPY & STAT ==========
<N> MapPoints : 5
*/
