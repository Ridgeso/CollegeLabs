#pragma once
#include <string>


struct LData
{
public:
	LData() { }
	virtual ~LData() { }

	virtual LData* Clone() const { return new LData(*this); }
	virtual void Print() const { }
	virtual bool Compare(const LData* other) const { return false; };

private:
};

std::ostream& operator<<(std::ostream& os, const LData& data);


struct IntData : public LData
{
public:
	IntData(int data)
		: m_Data(data)
	{ }

	~IntData() override;

	IntData* Clone() const override;
	void Print() const override;
	bool Compare(const LData* other) const override;

	friend std::ostream& operator<<(std::ostream& os, const IntData& data);

private:
	int m_Data;
};

std::ostream& operator<<(std::ostream& os, const IntData& data);


struct StringData : public LData
{
public:
	StringData(const std::string& data)
		: m_Data(data)
	{ }

	~StringData() override;

	StringData* Clone() const override;
	void Print() const override;
	bool Compare(const LData* other) const override;

	friend std::ostream& operator<<(std::ostream& os, const StringData& data);

private:
	std::string m_Data;
};

std::ostream& operator<<(std::ostream& os, const StringData& data);


struct Boolean : public LData
{
public:
	Boolean(bool data)
		: m_Data(data)
	{ }

	~Boolean() override;

	Boolean* Clone() const override;
	void Print() const override;
	bool Compare(const LData* other) const override;

	friend std::ostream& operator<<(std::ostream& os, const Boolean& data);

private:
	bool m_Data;
};

std::ostream& operator<<(std::ostream& os, const Boolean& data);
