#include <iostream>
#include "../SingleLinkedList/List.h"

int main()
{
	List list_1{ 1,2,3,4,5 };
	List list_2{ 1,5,10,15 };
	list_1 = std::move(list_2);
	List expected{ 1,5,10,15 };
	std::cout << list_1;
	
	return 0;
}