#include "Factory.h"


std::vector<TestObj*> Factory::s_TestObjList = {};
TestObj* Factory::s_pattern = nullptr;


TestObj* Factory::produce()
{
    TestObj* newTestObj;

    newTestObj = s_pattern ? new TestObj(*s_pattern) : new TestObj();

    s_TestObjList.push_back(newTestObj);
    return newTestObj;
}

void Factory::prototype(const TestObj& newPatern)
{
    if (s_pattern != nullptr)
        delete s_pattern;
    
    s_pattern = new TestObj(newPatern);
}

void Factory::erase()
{
    for (TestObj* testObj : s_TestObjList)
        delete testObj;

    delete s_pattern;
}
