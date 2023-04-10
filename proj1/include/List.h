#pragma once
#include "Data.h"

class List
{
public:
	enum ListOrder { Begin, End };

	List()
		: m_Head(nullptr)
	{ }
	List(const List& copy);
	~List();

	List& insert(const Data& data, ListOrder order = End);
	void print() const;
	void Reverse();
	void Clean();

private:
	struct Node
	{
		Data* data;
		Node* next;
	};

	Node* GetTail() const;

private:
	Node* m_Head;
	
};