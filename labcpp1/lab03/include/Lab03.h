#include <iostream>
#include <stdlib.h>

void AddStudent(int* numberOfStudents, char*** namesList, int** yearsList, const char* name, const int year);

void Cat(const int n, char** list);
void Cat(const int n, int* list);

void ClearList (int numberOfStudents, char*** namesList);
void ClearList(int numberOfStudents, int** yearsList);