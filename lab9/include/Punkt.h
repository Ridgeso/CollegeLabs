#pragma once
#include <iostream>
#include <string>

class Punkt
{
public:
    Punkt(const std::string& name, int x, int y);

    Punkt& operator=(const Punkt& other);

    template<int Wspolerzedna>
    int wsp() const { return m_Wsp[Wspolerzedna]; }

    template<typename T>
    static T min(T left, T right)
    {
        return left < right ? left : right;
    }

    bool operator<(const Punkt& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Punkt& p);

private:
    std::string m_Name;
    // int m_X, m_Y;
    int m_Wsp[2];
};

std::ostream& operator<<(std::ostream& os, const Punkt& p);

template<typename T>
void swap(T& left, T& right)
{
    T temp = left;
    left = right;
    right = temp;
}