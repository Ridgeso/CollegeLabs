#include <iostream>
#include <stdlib.h>

void AddStudent(
    int* numberOfStudents,
    char*** namesList,
    char*** surnamesList,
    int** yearsList,
    const char* firstName,
    const char* secondName,
    const char* surname,
    const int year
);

void PrintListContent(const int n, char** list);
void PrintListContent(const int n, int* list);
void PrintListContent(const int n, char** namesList, char** surnamesList, int* yearsList);
void ClearStudents (int* numberOfStudents, char*** namesList, char*** surnamesList, int** yearsList);