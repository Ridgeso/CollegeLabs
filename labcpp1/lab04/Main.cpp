// Prosze dopisac kod, dodac nowe pliki, tak aby program wykonywal
// sie, a wynik jego dzialania byl taki sam jak podany na końcu tego
// pliku.

// Prosze napisac klasę MapPoint, ktora reprezentuje punkt na
// mapie skladajacy sie z nazwy, dlugosci (longitude) i szerokosci
// (latitude) geograficznej bez oznaczania polkol.

// Metoda mp.distanceMP(dest) tworzy nowy punkt na mapie o zadanym
// polozeniu, ktore jest różnicą z polozen
// podanych punktow czyli x_new = dest.x - mp.x

// Metoda mp.distanceVal(dest) zwraca moduł z punktu tworzonego tak samo
// jak w metodzie mp.distanceMP(dest)

// Należy zadbać o uwzględnienie const w metodach klasy.

// Pliku Main.cpp, nie wolno modyfikowac.

// Ostateczny program powinien byc przyjazny dla programisty (miec
// czytelny i dobrze napisany kod).

// Przy wykonaniu zadania nie wolno korzystac z internetu, notatek,
// ani zadnych innych materialow (w tym własnych wczesniej
// przygotowanych plikow oprócz makefile)

// Kody źródłowe muszą znajdować się w katalogu do którego nikt oprócz
// właściciela nie ma praw dostępu.
// Rozwiazanie (czyli dodane pliki i Main.cpp należy wgrać do UPEL 
// jako archiwum tar.gz
// UWAGA:
// * archiwum powinno zawierać katalog z zadaniem, np. lab04/
// * archiwum nie powinno zawierać katalogu build/


#include <iostream>
#include "MapPoint.h"
#include "MapPoint.h"

int main() {
  using std::cout;

  cout<<"========== KRK ==========\n";
  MapPoint krk;
  krk.set_latitude(19.9383);
  krk.set_longitude(50.0613);
  krk.print();

  cout<<"========== NYC ==========\n";
  const double nyc_latitude = 40.7127;
  const double nyc_longitude = -74.0059;
  MapPoint nyc;
  nyc.set_coordinates (nyc_latitude, nyc_longitude);
  nyc.print();

  cout<<"========== PORTO & Null Island ==========\n";
  MapPoint porto;
  porto.set_coordinates(41.1621, -8.6219);
  porto.print();
  const MapPoint nullIsland;
  nullIsland.print();

  cout<<"========== DISTANCE ==========\n";
  porto.distanceMP(nullIsland).print();
  cout<<"Val: "<<nullIsland.distanceVal(porto) << std::endl;

  std::cin.get();
  return 0;
}
/** Wynik dzialania programu:
========== KRK ==========
Point: (19.9383, 50.0613)
========== NYC ==========
Point: (40.7127, -74.0059)
========== PORTO & Null Island ==========
Point: (41.1621, -8.6219)
Point: (0, 0)
========== DISTANCE ==========
Point: (-41.1621, 8.6219)
Val: 42.0554
*/
