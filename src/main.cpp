#include <iostream>
#include <functional>
#include <cmath>
#include "Utilities.hpp"
#include "HashTable.hpp"
#include "ClosedAddressingTable.hpp"
#include "CuckooHashingTable.hpp"
#include "SinglyLinkedList.hpp"
#include "AVL.hpp"
#include "OpenAddressingHashTable.hpp"
#include "Menu.hpp"

int main()
{
	DataTypeMenu m1;
	m1.run();
	/*
	CuckooHashingTable<int, int> ht(11);

	ht.insert(20, 20);
	ht.insert(50, 50);
	ht.insert(53, 53);
	ht.insert(75, 75);
	ht.insert(100, 100);
	ht.insert(67, 67);
	ht.insert(105, 105);
	ht.insert(36, 36);
	ht.insert(3, 3);
	ht.insert(39, 39);

	ht.display();
	*/

	/*
	measurePerformance(1000, 10000);
	measurePerformance(1000, 20000);
	measurePerformance(1000, 30000);
	measurePerformance(1000, 40000);
	measurePerformance(1000, 50000);
	measurePerformance(1000, 60000);
	measurePerformance(1000, 70000);
	measurePerformance(1000, 80000);
	measurePerformance(1000, 90000);
	measurePerformance(1000, 100000);
	measurePerformance(1000, 110000);
	measurePerformance(1000, 120000);
	measurePerformance(1000, 130000);
	measurePerformance(1000, 140000);
	measurePerformance(1000, 150000);
	measurePerformance(1000, 200000);
	measurePerformance(1000, 250000);
	measurePerformance(1000, 300000);
	measurePerformance(1000, 400000);
	measurePerformance(1000, 500000);
	*/
	return 0;
}