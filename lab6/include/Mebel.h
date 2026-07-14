#pragma once
#include <iostream>

class Mebel
{
public:
    Mebel(int width, int height, int deepth);
    virtual ~Mebel();

    virtual std::string Print() const;

    friend std::ostream& operator<<(std::ostream& os, const Mebel& mebel);

protected:
    int m_Width, m_Height, m_Deepth;

private:
};

std::ostream& operator<<(std::ostream& os, const Mebel& mebel);