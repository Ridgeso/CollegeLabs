#pragma once
#include <iostream>

template<typename T, int Rows, int Colums>
class Matrix
{
public:
    Matrix()
    {
        reset(static_cast<T>(0));
    }

    Matrix(T val)
    {
        reset(val);
    }

    void reset(T val);

    template<typename U>
    void add(const Matrix<U, Rows, Colums>& other)
    {
        for (int i = 0; i < Rows; i++)
            for (int j = 0; j < Colums; j++)
                m_Data[i][j] += other.at(i, j);    
    }

    template<int row, int col>
    T& at() { return m_Data[row][col]; }

    T& at(int row, int col) { return m_Data[row][col]; }
    T at(int row, int col) const { return m_Data[row][col]; }

private:
    T m_Data[Rows][Colums];
};


template<typename T, int Rows, int Colums>
void Matrix<T, Rows, Colums>::reset(T val)
{
    for (int i = 0; i < Rows; i++)
        for (int j = 0; j < Colums; j++)
            m_Data[i][j] = val;
}

template<typename T, int Rows, int Colums>
std::ostream& operator<<(std::ostream& os, const Matrix<T, Rows, Colums>& mat)
{
    for (int j = 0; j < Colums; j++)
    {
        for (int i = 0; i < Rows; i++)
            os << " " << mat.at(i, j);
        os << std::endl;
    }

    return os;
}