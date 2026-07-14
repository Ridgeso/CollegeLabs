#pragma once

#include <iostream>
#include <array>
#include "ComplexNumber.h"

namespace Math
{

    class Vector
    {
    public:
        //
        // Konstruktory
        //
        Vector();
        // Konstructor double
        Vector(double value);
        // Domyslny Destruktor
        ~Vector();

        //
        // zwracanie x,
        //
        ComplexNumber& X();

        //
        // nadaja wartosc x, y, z
        //
        Vector& SetY(double x, double y);
        Vector& SetZ(double x, double y);

        //
        // nadaja Kopiowanie x, y, z
        //
        Vector& SetX(const ComplexNumber& x);

        //
        // wypisuje Vector
        //
        void Print() const;

#if DEBUG
        const std::string& ToString() const { return m_DebugName; }
#endif

    private:
        static const int m_numOfNumbers = 3;
        std::array<ComplexNumber, m_numOfNumbers> m_numbers;


#if DEBUG
        std::string m_DebugName = "Vector";
#endif
    };

#if DEBUG
    namespace Log
    {

        template<typename T>
        void LogVector(T arg)
        {
            std::cout << arg << std::endl;
        }

        template<typename T, typename... Args>
        void LogVector(T& arg,Args&&... args)
        {
            std::cout << arg << " | ";
            LogVector(args...);
        }
    }
#endif
}

#if DEBUG
std::ostream& operator<<(std::ostream& os, const Math::Vector& vec)
{
    os << vec.ToString();
    return os;
}
#endif