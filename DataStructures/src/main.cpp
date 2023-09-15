#include <iostream>
#include "utility.h"

int main()
{
	std::cout << "My Simple Array Implementation\n";
	typedef uint32_t myType;

	HaKai::Array<myType> hakaiArray(4);
	
	std::cout << "Array Operations: \n";
	std::cout << "1: Add\n";
	std::cout << "2: Remove\n";
	std::cout << "3: Resize\n";
	std::cout << "4: RemoveFrom\n";

	while (true)
	{
		char mode;
		std::cout << "Input the mode from 1-4:\n";
		std::cin >> mode;

		if (mode == '1')
		{
			std::cout << "What element to add?\n";
			myType element;
			std::cin >> element;
			hakaiArray.add(element);
		}
		else if (mode == '2')
		{
			std::cout << "What element to remove?\n";
			myType element;
			std::cin >> element;
			uint32_t arraySize = 0;
			uint32_t* ele = hakaiArray.remove(element, arraySize);
			std::cout << "Index from which element was removed: [";
			for (uint32_t i = 0; i < arraySize; i++)
				std::cout << ele[i] << ", ";
			std::cout << "]\n";
		}
		else if (mode == '3')
		{
			std::cout << "What capacity to resize to?\n";
			size_t capacity;
			std::cin >> capacity;
			hakaiArray.resize(capacity);
		}
		else if (mode == '4')
		{
			std::cout << "Which index to remove element from?\n";
			size_t index;
			std::cin >> index;
			std::cout << "Removed element: " << hakaiArray.removeFrom(index) << std::endl;
		}

		std::cout << "Array Size:" << hakaiArray.size() << std::endl;
		std::cout << "Array Capacity:" << hakaiArray.capacity() << std::endl;
		std::cout << "Array: [";
		for (size_t i = 0; i < hakaiArray.size(); i++)
			std::cout << hakaiArray[i] << ", ";
		std::cout << "]\n";
		
	}
}