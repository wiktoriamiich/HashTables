#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cstdlib>
#include <ctime>
#include <vector>
#include "Timer.hpp"
#include "ClosedAddressingTable.hpp"
#include "CuckooHashingTable.hpp"

std::vector<int> generateIntDataSet(int size, int seed = time(NULL), int start = 0, int end = 100000)
{
	srand(seed);
	std::vector<int> dataSet;

	for (int i = 1; i <= size; i++)
	{
		int random = (rand() % end) + start;
		dataSet.push_back(random);
	}

	return dataSet;
}

void measurePerformance(int repetitions, int dataSetSize)
{
	//Generate keys
	std::vector<int> keys = generateIntDataSet(dataSetSize);

	//Generate values
	std::vector<int> values = generateIntDataSet(dataSetSize);

	CuckooHashingTable<int, int> ht(dataSetSize * 2);

	for (int i = 0; i < dataSetSize; i++)
		ht.insert(keys[i], values[i]);

	double averageTime = 0.0;
	double sum = 0.0;
	double duration = 0.0;

	srand(time(NULL));

	//int valueToInsert(rand() % 10000);
	ht.insert(-1, -1);
	// measure time of operation

	for (int i = 0; i < repetitions; i++)
	{
		Timer timer;
		timer.start();
		ht.remove(-1);
		timer.stop();

		duration = timer.getDuration();
		sum += duration;

		ht.insert(-1, -1);
	}

	averageTime = sum / repetitions;

	std::cout << "Average time: " << averageTime << "ns\n";
}

#endif