#pragma once
#include <stdint.h>

namespace HaKai
{

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	////////////// Custom Array Implementation /////////////////////
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////


	template <typename T>
	class Array
	{
	public:
		Array(size_t size)
			: m_Capacity(size)
		{
			m_Buffer = new T[m_Capacity];
		}
		~Array()
		{
			delete[] m_Buffer;
		}
		
		const size_t size() const
		{
			return m_Size;
		}

		const size_t capacity() const
		{
			return m_Capacity;
		}

		T& operator[](size_t index)
		{
			if (index < m_Size)
				return *(T*)(m_Buffer + index);

			throw std::out_of_range("Index out of bounds");
		}

		// Manually resizing the array to accomodate "elements" amount
		// It supports both expansion/shrinking of array
		void resize(size_t capactiyToResizeTo)
		{
			if (capactiyToResizeTo <= 2)
				capactiyToResizeTo = 4;

			if (capactiyToResizeTo > m_Capacity)
			{
				T* tempArray = new T[capactiyToResizeTo];
				for (size_t i = 0; i < m_Size; i++)
					tempArray[i] = m_Buffer[i];
				delete[] m_Buffer;
				m_Buffer = tempArray;
			}
			else if (capactiyToResizeTo < m_Size)
			{
				for (size_t i = capactiyToResizeTo; i < m_Size; i++)
					m_Buffer[i] = '\0';
				m_Size = capactiyToResizeTo;
				m_Capacity = capactiyToResizeTo;
				resize((size_t)(capactiyToResizeTo * 1.5));
				return;
			}
			m_Capacity = capactiyToResizeTo;
		}

		void add(T& element)
		{
			if (m_Capacity == m_Size + 1)
			{
				m_Capacity = (size_t)(m_Capacity * 1.5);
				T* tempArray = new T[m_Capacity];
				for (size_t i = 0; i < m_Size; i++)
					tempArray[i] = m_Buffer[i];
				tempArray[m_Size] = '\0';
				delete[] m_Buffer;
				m_Buffer = tempArray;
			}

			m_Buffer[m_Size] = element;
			m_Buffer[m_Size+1] = '\0';
			m_Size++;
		}

		// Removes the element and returns an array of
		// indices from where the element was removed
		uint32_t* remove(T& element, uint32_t& arraySize)
		{
			// Find all the matches to create space for the array
			for (uint32_t i = 0; i < m_Size; i++)
			{
				if (element == m_Buffer[i])
				{
					arraySize++;
				}
			}
			if (!arraySize)
				return nullptr;
			uint32_t* myArray = new uint32_t[arraySize];

			// Remove elements here
			uint32_t loopCounter = 0;
			for (uint32_t i = 0; i < m_Size; i++)
			{
				while (element == m_Buffer[i])
				{
					// Copy everything from right side and make it fall one step back
					for (uint32_t j = i; j < m_Size; j++)
					{
						m_Buffer[j] = m_Buffer[j + 1];
					}

					m_Size--;
					m_Buffer[m_Size] = '\0';
					uint32_t index = i + loopCounter;
					myArray[loopCounter] = index;
					loopCounter++;
				}
			}
			return myArray;
		}

		// Removes element from specified index and
		// returns the element from that index
		T removeFrom(size_t index)
		{
			if (index < m_Size)
			{
				T myELement = m_Buffer[index];
				for (size_t i = index; i < m_Size; i++)
				{
					m_Buffer[i] = m_Buffer[i + 1];
				}
				m_Buffer[m_Size - 1] = '\0';
				m_Size--;
				return myELement;
			}
			throw std::out_of_range("Index out of bounds");
		}


	private:
		T* m_Buffer;
		// This is actual capacity
		size_t m_Capacity;
		// These are number of elements occupied and is always < m_Capacity
		size_t m_Size = 0;
	};
}