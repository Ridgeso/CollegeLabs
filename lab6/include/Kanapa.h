#pragma once
#include "Sofa.h"
#include "Lozko.h"


class Kanapa : public Sofa, public Lozko
{
public:
    Kanapa(int width, int height, int deepth, int sitWidth, int sleepWidth);
    ~Kanapa() override;

    std::string Print() const override;
};
