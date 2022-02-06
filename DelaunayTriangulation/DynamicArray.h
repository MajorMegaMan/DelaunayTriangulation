#pragma once

template <class T>
class DynamicArray
{
	T* m_valueArray = nullptr;
	int m_size = 0;
	int m_capacity = 0;

public:
	DynamicArray()
	{
		m_capacity = 4;
		m_valueArray = new T[m_capacity];
	}

	DynamicArray(const DynamicArray& other) = delete;
	DynamicArray& operator=(const DynamicArray& other) = delete;

	~DynamicArray()
	{
		delete[] m_valueArray;
		m_valueArray = nullptr;
	}

	void PushBack(const T& value)
	{
		if (m_size == m_capacity)
		{
			// resize array
			Resize();
		}

		m_valueArray[m_size] = value;
		m_size++;
	}

	void Clear()
	{
		m_size = 0;
	}

	T& GetValue(int index)
	{
		return m_valueArray[index];
	}

	T* GetArray()
	{
		return m_valueArray;
	}

	int GetSize()
	{
		return m_size;
	}

private:
	void Resize()
	{
		// allocate new array
		m_capacity = m_capacity * 2;
		T* newArray = new T[m_capacity];
		
		// copy old elements
		for (int i = 0; i < m_size; i++)
		{
			newArray[i] = m_valueArray[i];
		}

		// delete old
		delete[] m_valueArray;
		// assign to new
		m_valueArray = newArray;
	}
};