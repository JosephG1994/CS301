#include "stdafx.h"
#include "LinkedQue.h"

struct NodeType
{
	patient info;
	NodeType* next;
};

LinkedQue::LinkedQue(void)
{
	front = NULL;
	rear = NULL;
	length = 0;
}

LinkedQue::~LinkedQue(void)
{
	MakeEmpty();
}

void LinkedQue::MakeEmpty()
{
	NodeType* tempPtr;

	while (front != NULL)
	{
		tempPtr = front;
		front = front->next;
		delete tempPtr;
	}
	rear = NULL;
}

bool LinkedQue::IsEmpty() const
{
	return (front == NULL);
}

bool LinkedQue::IsFull() const
{
	NodeType* location;
	try {
		location = new NodeType;
		delete location;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}

void LinkedQue::Enqueue(patient newItem)
{
	if (IsFull())
		throw FullQueue();
	else
	{
		NodeType* newNode;

		newNode = new NodeType;
		newNode->info = newItem;
		newNode->next = NULL;
		if (rear == NULL)
		{
			front = newNode;
		}
		else
		{
			rear->next = newNode;
		}
		rear = newNode;
		length++; 
	}
}

void LinkedQue::Dequeue(patient& item)
{
	if (IsEmpty())
	{
		throw EmptyQueue();
	}
	else
	{
		NodeType* tempPtr;

		tempPtr = front;
		item = front->info;
		front = front->next;
		if (front == NULL)
		{
			rear = NULL;
		}
		delete tempPtr;
		length--;
	}
}

int LinkedQue::GetLength() const
{
	return length;
}
