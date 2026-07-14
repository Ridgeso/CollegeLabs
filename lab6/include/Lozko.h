#pragma once
#include "Mebel.h"

class Lozko : public Mebel
{
public:
    Lozko(int width, int height, int deepth, int sleepWidth);
    ~Lozko() override;

    std::string Print() const override;

private:
    int m_SleepWidth;
};
