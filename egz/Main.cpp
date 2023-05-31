#include <iostream>
#include <vector>
#include <memory>


class Worker
{
public:
	virtual void Task() { }
};

class Miner : public Worker
{
public:
	void Task() override { std::cout << "Mined\n"; }
};


class Seller : public Worker
{
public:
	void Task() override { std::cout << "Sold\n"; }
};

class Factory
{
public:
	void AddWorker(Worker* w)
	{
		m_Shift.push_back(w);
	}

	void StartShift()
	{
		for (auto w: m_Shift)
			w->Task();
	}

	~Factory()
	{
		for (auto w : m_Shift)
			delete w;
	}

private:
	std::vector<Worker*> m_Shift;
};


int main()
{
	Factory wiel;

	wiel.AddWorker(new Miner());
	wiel.AddWorker(new Miner());
	wiel.AddWorker(new Seller());

	wiel.StartShift();

	return 0;
}