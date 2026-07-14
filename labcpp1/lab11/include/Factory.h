#pragma once
#include <vector>

#include "TestObj.h"


class Factory
{
public:
    //
    // Creates another Object of TestOjb
    //
    static TestObj* produce();

    //
    // Set new pattern for function produce
    //
    static void prototype(const TestObj& newPatern);

    //
    // clear all TestObj allocated on the heap
    //
    static void erase();

private:
    static std::vector<TestObj*> s_TestObjList;
    static TestObj* s_pattern;
};