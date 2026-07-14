// Prosze dopisac kod, dodac nowe pliki, tak aby program wykonywal się
// a wynik jego dzialania byl taki sam jak podany na końcu tego pliku
//
// Pliku Main.cpp, nie wolno modyfikowac.
//
// Prosze napisac funkcje wykonujace operacje na tablicach
// reprezentujacych liste studentow.
//
// W tablicy "namesList" przechowywane sa pierwsze i drugie imie
// studenta oddzielone pojedyńczą spacją.

// W tablicy "surnamesList" przechowywane sa nazwiska studentow.

// W tablicy "yearsList" przechowywane sa lata na ktorych studiuja
// studenci.

// UWAGA: Tablice powinny dostosowywac sie do liczby elementow, ktore maja 
// byc w nich przechowywane.

// Prosze zwrocic uwage na dobre zarzadzanie pamiecia.
// Ostateczny program powinien byc przyjazny dla programisty
// (miec czytelny i dobrze napisany kod).
//
// Przy wykonaniu zadania nie wolno korzystac z internetu, notatek,
// ani żadnych innych materialow (w tym własnych wczesniej
// przygotowanych plikow oprócz makefile, chyba że polecenie stanowi inaczej)
//
// Kody źródłowe muszą znajdować się w katalogu do którego nikt oprócz
// właściciela nie ma praw dostępu.
// Rozwiazanie (czyli dodane pliki i Main.cpp należy wgrać do UPEL 
// jako archiwum tar.gz
// UWAGA:
// * archiwum powinno zawierać katalog z zadaniem, np. lab02/
// * archiwum nie powinno zawierać katalogu build/
// * tworzenie archiwum: tar -czvf nazwa.tar.gz zad/

#include "StudentList.h"

int main ()
{
  int numberOfStudents = 0;
  char** namesList = NULL;
  char** surnamesList = NULL;
  int* yearsList = NULL;

  const char* firstName = "Spike";
  const char* secondName = "Jozef";
  const char* surname = "Spiegel";
  AddStudent(&numberOfStudents, &namesList, &surnamesList, &yearsList, firstName, secondName, surname, 3);

  firstName = "Rick";
  secondName = "Albert";
  surname = "Sanchez";
  AddStudent(&numberOfStudents, &namesList, &surnamesList, &yearsList, firstName, secondName, surname, 7);

  firstName = "Sterling";
  secondName = "Malory";
  surname = "Archer";
  AddStudent(&numberOfStudents, &namesList, &surnamesList, &yearsList, firstName, secondName, surname, 1);

  std::cout<<"Only names:\n";
  PrintListContent (numberOfStudents, namesList);

  std::cout<<"\nOnly years:\n";
  PrintListContent (numberOfStudents, yearsList);

  std::cout<<"\nEverything:\n";
  PrintListContent (numberOfStudents, namesList, surnamesList, yearsList);

  ClearStudents (&numberOfStudents, &namesList, &surnamesList, &yearsList);

  return 0;
}
/* wynik dzialania programu:
Only names:
Spike Jozef
Rick Albert
Sterling Malory

Only years:
3
7
1

Everything:
Spiegel, Spike Jozef - year 3
Sanchez, Rick Albert - year 7
Archer, Sterling Malory - year 1
*/
