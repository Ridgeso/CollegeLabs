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

bool IntData::Compare(const LData& other) const
{
	try
	{
		const IntData& oth = dynamic_cast<const IntData&>(other);
		return m_Data == oth.m_Data;
	}
	catch (std::bad_cast& e)
	{
		return false;
	}
}

std::ostream& operator<<(std::ostream& os, const IntData& data)
{
	os << data.m_Data;
	return os;
}

std::string IntData::ToString() const
{
	return std::to_string(m_Data);
}


FloatData::~FloatData()
{
}

FloatData* FloatData::Clone() const
{
	return new FloatData(*this);
}

void FloatData::Print() const
{
	std::cout << m_Data;
}

bool FloatData::Compare(const LData& other) const
{
	try
	{
		const FloatData& oth = dynamic_cast<const FloatData&>(other);
		return m_Data == oth.m_Data;
	}
	catch (std::bad_cast& e)
	{
		return false;
	}
}

std::ostream& operator<<(std::ostream& os, const FloatData& data)
{
	os << data.m_Data;
	return os;
}

std::string FloatData::ToString() const
{
	return std::to_string(m_Data);
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

bool StringData::Compare(const LData& other) const
{
	try
	{
		const StringData& oth = dynamic_cast<const StringData&>(other);
		return m_Data == oth.m_Data;
	}
	catch (std::bad_cast& e)
	{
		return false;
	}
}

std::ostream& operator<<(std::ostream& os, const StringData& data)
{
	os << data.m_Data;
	return os;
}

std::string StringData::ToString() const
{
	return m_Data;
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

bool Boolean::Compare(const LData& other) const
{
	try
	{
		const Boolean& oth = dynamic_cast<const Boolean&>(other);
		return m_Data == oth.m_Data;
	}
	catch (std::bad_cast& e)
	{
		return false;
	}
}

std::ostream& operator<<(std::ostream& os, const Boolean& data)
{
	os << data.m_Data ? "true" : "false";
	return os;
}

std::string Boolean::ToString() const
{
	return m_Data ? "true" : "false";
}
