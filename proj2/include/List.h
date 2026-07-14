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

	List& insert(const LData& data, ListOrder order = End);
	void print() const;
	void Reverse();
	void Clean();

	LData* clone_if_exists(const LData& target) const;
	List numeric() const;
	List non_numeric() const;

private:
	struct Node
	{
		LData* data;
		Node* next;
	};

	Node* GetTail() const;

private:
	Node* m_Head;
	
};