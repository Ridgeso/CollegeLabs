#include <iostream>
#include "List.h"

List::List(const List& copy)
	: m_Head(nullptr)
{
	if (!copy.m_Head)
		return;

	const Node* tmp = copy.m_Head;
	m_Head = new Node{ tmp->data->Clone(), nullptr };

	Node* tail = m_Head;
	while (tmp = tmp->next)
	{
		tail->next = new Node{ tmp->data->Clone(), nullptr };
		tail = tail->next;
	}
}

List::~List()
{
	Clean();
}

List& List::insert(const LData& data, List::ListOrder order)
{
	if (m_Head == nullptr)
	{
		m_Head = new Node{ data.Clone(), nullptr };
		return *this;
	}

	switch (order)
	{
		case Begin:
		{
			m_Head = new Node{ data.Clone(), m_Head };
			break;
		}
		case End:
		{
			GetTail()->next = new Node{ data.Clone(), nullptr };
			break;
		}
		default:
		{
			break;
		}
	}

	return *this;
}

void List::print() const
{
	std::cout << '[';
	if (m_Head)
	{
		const Node* tmp = m_Head;
		while (tmp->next)
		{
			tmp->data->Print();
			std::cout << ", ";
			tmp = tmp->next;
		}
		tmp->data->Print();
	}
	std::cout << ']' << std::endl;
}

void List::Reverse()
{
	Node* curr = m_Head;
	Node* next = nullptr, * prev = nullptr;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	m_Head = prev;
}

void List::Clean()
{
	Reverse();
	Node* tmp = m_Head;
	while (tmp)
	{
		m_Head = m_Head->next;
		delete tmp->data, tmp;
		tmp = m_Head;
	}
}


LData* List::clone_if_exists(const LData& target) const
{
	for (Node* tmp = m_Head; tmp != nullptr; tmp = tmp->next)
	{
		if (tmp->data->Compare(&target) == true)
			return tmp->data->Clone();
	}
	return nullptr;
}


List List::numeric() const
{
	List numericList;
	for (Node* tmp = m_Head; tmp != nullptr; tmp = tmp->next)
	{
		const IntData* castedNumeric = dynamic_cast<IntData*>(tmp->data);
		if (castedNumeric)
			numericList.insert(*tmp->data);
	}
	return std::move(numericList);
}

List List::non_numeric() const
{
	List nonNumericList;
	for (Node* tmp = m_Head; tmp != nullptr; tmp = tmp->next)
	{
		const IntData* castedNonNumeric = dynamic_cast<IntData*>(tmp->data);
		if (castedNonNumeric == nullptr)
			nonNumericList.insert(*tmp->data);
	}
	return std::move(nonNumericList);
}


List::Node* List::GetTail() const
{
	if (!m_Head)
		return m_Head;
	
	Node* tmp = m_Head;
	while (tmp->next)
		tmp = tmp->next;
	
	return tmp;
}