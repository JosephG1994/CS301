#pragma once
#include <string>
using namespace std;

class FullQueue
{};

class EmptyQueue
{};

// Patient Information
struct patient {
	string name;
	int specialty;
	int age;
	string emergencyInd;
};

struct NodeType;

class LinkedQue
{
public:
	LinkedQue();
	~LinkedQue();
	void MakeEmpty();
	bool IsEmpty() const;	
	bool IsFull() const;
	void Enqueue(patient);	
	void Dequeue(patient&);	
	int GetLength() const;	
private:
	NodeType* front;		
	NodeType* rear;		
	int length;			
};