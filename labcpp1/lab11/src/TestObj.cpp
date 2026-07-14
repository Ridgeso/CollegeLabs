#include <iostream>

#include "TestObj.h"


TestObj::TestObj()
    : m_Name("default")
{
    std::cout << "TestObj::TestObj()" << std::endl;
}

TestObj::TestObj(const std::string& name)
    : m_Name(name)
{
    std::cout << "TestObj::TestObj(\"" << m_Name << "\")" << std::endl;
}

TestObj::TestObj(const TestObj& obj)
    : m_Name(obj.m_Name)
{
    std::cout << "TestObj::TestObj(TestObj(\"" << m_Name << "\"))" << std::endl;
}

TestObj::~TestObj()
{
    std::cout << "~TestObj(): ";
    
    if (m_Name == "")
        std::cout << "default";
    else
        std::cout << m_Name;

    std::cout << std::endl;
}

const std::string& TestObj::name() const
{
    return m_Name;
}