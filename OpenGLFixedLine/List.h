#pragma once
class List
{
public:
	List();
	~List();
public:
	void* m_Next;

	template<typename T>
	T* Next()
	{
		return (T*)m_Next;
	}
};