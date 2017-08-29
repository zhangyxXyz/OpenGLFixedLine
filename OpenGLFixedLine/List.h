#pragma once
class List
{
public:
	List() :m_Next(nullptr) {}
	~List();
public:
	List* m_Next;

	template<typename T>
	T* Next()
	{
		return (T*)m_Next;
	}

	void Push(List* next)
	{
		List* lastNode = this;
		while (nullptr != lastNode->m_Next)
		{
			lastNode = lastNode->Next<List>();
		}
		lastNode->m_Next = next;
	}
	// Todo: delete function
};

class RenderableObject : public List
{
public:
	virtual void Draw()
	{
		if (m_Next != nullptr)
		{
			Next<RenderableObject>()->Draw();
		}
	}
};