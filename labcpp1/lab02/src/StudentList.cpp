#include "StudentList.h"
#include <stdlib.h>
#include <string.h>


void AddStudent(
    int* numberOfStudents,
    char*** namesList,
    char*** surnamesList,
    int** yearsList,
    const char* firstName,
    const char* secondName,
    const char* surname,
    const int year
)
{
    (*numberOfStudents)++;
    *namesList = (char**)realloc(*namesList, sizeof(char*) * (*numberOfStudents));
    *surnamesList = (char**)realloc(*surnamesList,  sizeof(char*) * (*numberOfStudents));
    *yearsList = (int*)realloc(*yearsList, sizeof(int*) * (*numberOfStudents));

    (*namesList)[*numberOfStudents - 1] = (char*)malloc(sizeof(char) * (strlen(firstName) + strlen(secondName) + 2));
    (*surnamesList)[*numberOfStudents - 1] = (char*)malloc(sizeof(char) * (strlen(surname) + 1));
    
    strcpy((*namesList)[*numberOfStudents - 1], firstName);
    strcat((*namesList)[*numberOfStudents - 1], " ");
    strcat((*namesList)[*numberOfStudents - 1], secondName);

    strcpy(surnamesList[0][*numberOfStudents - 1], surname);
    
    (*yearsList)[*numberOfStudents - 1] = year;
}

void PrintListContent(const int n, char** list)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << list[i] << std::endl;
    }
}

void PrintListContent(const int n, int* list)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << list[i] << std::endl;
    }
}

void PrintListContent(const int n, char** namesList, char** surnamesList, int* yearsList)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << surnamesList[i] << ", " << namesList[i] << " - years " << yearsList[i] << std::endl;
    }
}

void ClearStudents (int* numberOfStudents, char*** namesList, char*** surnamesList, int** yearsList)
{
    for (int i = 0; i < *numberOfStudents; i++)
    {
        free((*namesList)[i]);
        free((*surnamesList)[i]);
    }

    free(*namesList);
    free(*surnamesList);
    free(*yearsList);
}
