#include "Lab03.h"
#include <stdlib.h>
#include <string.h>


void AddStudent(int* numberOfStudents, char*** namesList, int** yearsList, const char* Name, const int year)
{
    (*numberOfStudents)++;

    // Tworzenie nowych tablic pasujacych wielkoscia
    char** newNamesList = new char*[*numberOfStudents];
    int* newYearsList = new int[*numberOfStudents];

    // Kopiowanie starych danych do nowych tablic
    for(int i = 0; i < *numberOfStudents - 1; i++)
    {
        newNamesList[i] = new char[strlen((*namesList)[i]) + 1];
        strcpy(newNamesList[i], (*namesList)[i]);

        newYearsList[i] = (*yearsList)[i];
    }
    std::cout << "cos tam" << std::endl;
    // Wkladanie nowych danych do nowych tablic
    newNamesList[*numberOfStudents - 1] = new char[strlen(Name) + 1];
    strcpy(newNamesList[*numberOfStudents - 1], Name);

    newYearsList[*numberOfStudents - 1] = year;

    // Usuwanie wyciekow pamieci i zamiana HEADow list
    for(int i = 0; i < *numberOfStudents - 1; i++)
    {
        delete[] (*namesList)[i];
    }
    delete[] *namesList;
    delete[] *yearsList;

    *namesList = newNamesList;
    *yearsList = newYearsList;
}

void Cat(const int n, char** list)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << list[i] << std::endl;
    }
}

void Cat(const int n, int* list)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << list[i] << std::endl;
    }
}

void ClearList(int numberOfStudents, char*** namesList)
{
    // Usuwanie pojedynczych elementow
    for (int i = 0; i < numberOfStudents; i++)
        delete[] (*namesList)[i];

    delete[] *namesList;
}

void ClearList(int numberOfStudents, int** yearsList)
{
    delete[] *yearsList;
}
