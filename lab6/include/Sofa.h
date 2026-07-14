#pragma once
#include "Mebel.h"

class Sofa : public Mebel
{
public:
    Sofa(int width, int height, int deepth, int sitWidth);
    ~Sofa() override;

    std::string Print() const override;

private:
    int m_SitWidth;
};
