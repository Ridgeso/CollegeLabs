//Extremely simple vector and matrix classes by Janusz Malinowski. 
#include <stdio.h>
#pragma once

struct Vector
{
	double data[3];
	
	Vector();
	void Print(void);
	void Set(double d1,double d2);
	Vector operator+(const Vector& other) const;
	Vector operator-(const Vector& other) const;
	double GetX();
	double GetY();
};

struct Matrix
{
	double data[3][3];

	Matrix();
	void Print(void);
	Matrix operator*(const Matrix);
	friend Vector operator*(const Matrix,const Vector);
};

