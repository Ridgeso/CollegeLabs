#pragma once

#include <string>


class TestObj
{
public:
    
    //
    // default constructors and destructors
    //
    TestObj();
    TestObj(const std::string& name);
    TestObj(const TestObj& obj);
    
    ~TestObj();

    //
    // Getter for m_Name
    //
    const std::string& name() const;

private:
    std::string m_Name;
};