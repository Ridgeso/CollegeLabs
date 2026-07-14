#pragma once

#include <string>
#include <set>

class Wektor2D
{
public:
    Wektor2D(int X);
    Wektor2D(const std::string& name, int X, int Y);

    void Wypisz() const;

    std::string GetName() const { return m_Name; }
    int GetX() const { return m_X; }
    int GetY() const { return m_Y; }
    void SetX(int X) { m_X = X; }
    void SetY(int Y) { m_Y = Y; }

    bool operator<(const Wektor2D& other) const { return m_X <= other.m_X; }

private:
    std::string m_Name;
    int m_X, m_Y;
};