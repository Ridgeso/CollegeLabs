#include <stdio.h>
#include "MyLibrary.h"

void PrintInfo(const std::string& str)
{
    std::cout << str << std::endl;
}

void PrintName(const std::string& name)
{
    PrintInfo(name);
}
