#pragma once
#include <string>


struct Data
{
public:
	Data() { }
	virtual ~Data() { }

	virtual Data* Clone() const { return new Data(*this); }
	virtual void Print() const { }
private:
};

struct IntData : public Data
{
public:
	IntData(int data)
		: m_Data(data)
	{ }

	~IntData() override;

	IntData* Clone() const override;
	void Print() const override;

private:
	int m_Data;
};

struct StringData : public Data
{
public:
	StringData(const std::string& data)
		: m_Data(data)
	{ }

	~StringData() override;

	StringData* Clone() const override;
	void Print() const override;

private:
	std::string m_Data;
};