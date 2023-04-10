#include <iostream>
#include "Data.h"

IntData::~IntData()
{
	std::cout << "~IntData()" << std::endl;
}

IntData* IntData::Clone() const
{
	return new IntData(*this);
}

void IntData::Print() const
{
	std::cout << m_Data;
}

StringData::~StringData()
{
	std::cout << "~StringData()" << std::endl;
}

StringData* StringData::Clone() const
{
	return new StringData(*this);
}

void StringData::Print() const
{
	std::cout << '"' << m_Data << '"';
}