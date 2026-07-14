#include <iostream>
#include "Data.h"


std::ostream& operator<<(std::ostream& os, const LData& data)
{
	data.Print();
	return os;
}


IntData::~IntData()
{
}

IntData* IntData::Clone() const
{
	return new IntData(*this);
}

void IntData::Print() const
{
	std::cout << m_Data;
}

bool IntData::Compare(const LData* other) const
{
	const IntData* oth = dynamic_cast<const IntData*>(other);
	if (oth)
		return m_Data == oth->m_Data;
	return false;
}

std::ostream& operator<<(std::ostream& os, const IntData& data)
{
	os << data.m_Data;
	return os;
}


StringData::~StringData()
{
}

StringData* StringData::Clone() const
{
	return new StringData(*this);
}

void StringData::Print() const
{
	std::cout << '"' << m_Data << '"';
}

bool StringData::Compare(const LData* other) const
{
	const StringData* oth = dynamic_cast<const StringData*>(other);
	if (oth)
		return m_Data == oth->m_Data;
	return false;
}

std::ostream& operator<<(std::ostream& os, const StringData& data)
{
	os << data.m_Data;
	return os;
}


Boolean::~Boolean()
{
}

Boolean* Boolean::Clone() const
{
	return new Boolean(*this);
}

void Boolean::Print() const
{
	std::cout << *this;
}

bool Boolean::Compare(const LData* other) const
{
	const Boolean* oth = dynamic_cast<const Boolean*>(other);
	if (oth)
		return m_Data == oth->m_Data;
	return false;
}

std::ostream& operator<<(std::ostream& os, const Boolean& data)
{
	if (data.m_Data)
		os << "true";
	else
		os << "false";
	return os;
}
