//Extremely simple vector and matrix classes by Janusz Malinowski. 
#include <stdio.h>
#pragma once

struct Vector4
{
    double data[4];
    Vector4();
    void Set(double x,double y,double z);
    double GetX();
    double GetY();
    double GetZ();
    Vector4 operator-(const Vector4 &);
    friend Vector4 operator*(const Vector4 &,double);
};

struct Matrix4
{
    double data[4][4];
    Matrix4();
    Matrix4 operator*(const Matrix4);
    friend Vector4 operator*(const Matrix4,const Vector4);
};


