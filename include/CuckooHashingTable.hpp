#ifndef CUCKOO_HASHING_TABLE_HPP
#define CUCKOO_HASHING_TABLE_HPP

#define CYCLE_LIMIT 5
#define ALPHA 0.618 // Golden ratio factorial part

#include "HashTable.hpp"
#include "Node.hpp"

#include <vector>
#include <functional>
#include <cmath>

template <typename T1, typename T2>
class CuckooHashingTable : public HashTable<T1, T2>
{
private:
	std::vector<Node<T1, T2>> array1_;
	std::vector<Node<T1, T2>> array2_;

	size_t size_;
	size_t elements_;
	float loadFactor_;

	size_t hash(int key, int type = 0);
	size_t hash(float key, int type = 0);
	size_t hash(char key, int type = 0);
	size_t hash(std::string key, int type = 0);

	void rehash();

public:
	CuckooHashingTable(size_t size);
	~CuckooHashingTable();

	void insert(T1 key, T2 value) override;
	void remove(T1 key) override;
	void display();

	size_t calculateLoadFactor();
};

// Initialize tables with default values
template <typename T1, typename T2>
CuckooHashingTable<T1, T2>::CuckooHashingTable(size_t size): size_(size), array1_(size), array2_(size), elements_(0), loadFactor_(0.0)
{
	
}

template <typename T1, typename T2>
CuckooHashingTable<T1, T2>::~CuckooHashingTable()
{
	// In progress
}

// Calculate index
template <typename T1, typename T2>
size_t CuckooHashingTable<T1, T2>::hash(int key, int type = 0)
{
	size_t hashValue = 0;

	switch (type)
	{
		case 0:
		{
			hashValue = key % size_;
			break;
		}

		// Multiplicatvie hashing
		case 1:
		{
			double nominator = static_cast<size_t>(ALPHA * key) % static_cast<size_t>(pow(2, 16));
			hashValue = std::floor(nominator / (pow(2, 16) / size_));
			break;
		}
	}

	return hashValue;
}

// Calculate index
template <typename T1, typename T2>
size_t CuckooHashingTable<T1, T2>::hash(float key, int type = 0)
{
	std::hash<float> hashFunction;
	size_t hashValue = 0;

	switch (type)
	{
		case 0:
		{
			hashValue = hashFunction(key);
			break;
		}

		// Multiplicatvie hashing
		case 1:
		{
			double nominator = static_cast<size_t>(ALPHA * key) % static_cast<size_t>(pow(2, 16));
			hashValue = std::floor(nominator / (pow(2, 16) / size_));
			break;
		}
	}

	return hashValue;
}

// Calculate index
template <typename T1, typename T2>
size_t CuckooHashingTable<T1, T2>::hash(char key, int type = 0)
{
	char asciiValue = int(key);
	size_t hashValue = 0;

	switch (type)
	{
		case 0:
		{
			hashValue = (asciiValue) % size_;
			break;
		}

		// Multiplicatvie hashing
		case 1:
		{
			double nominator = static_cast<size_t>(ALPHA * asciiValue) % static_cast<size_t>(pow(2, 16));
			hashValue = std::floor(nominator / (pow(2, 16) / size_));
			break;
		}
	}

	return hashValue;
}

// Calculate index
template <typename T1, typename T2>
size_t CuckooHashingTable<T1, T2>::hash(std::string key, int type = 0)
{
	int sum = 0;

	for (int i = 0; i < key.size(); i++)
		sum += int(key[i]) * pow(31, i);

	size_t hashValue = 0;

	switch (type)
	{
		case 0:
		{
			hashValue = sum % size_;
			break;
		}

		// Multiplicatvie hashing
		case 1:
		{
			double nominator = static_cast<size_t>(ALPHA * sum) % static_cast<size_t>(pow(2, 16));
			hashValue = std::floor(nominator / (pow(2, 16) / size_));
			break;
		}
	}

	return hashValue;
}

// Insert key-value pair at calculated index
template <typename T1, typename T2>
void CuckooHashingTable<T1, T2>::insert(T1 key, T2 value)
{
	int arrayIndex1 = hash(key, 0); 
	int arrayIndex2 = hash(key, 1);

	// If key is already present, do not insert
	if ((!array1_[arrayIndex1].isEmpty && array1_[arrayIndex1].key == key) || 
		(!array2_[arrayIndex2].isEmpty && array2_[arrayIndex2].key == key))
		return;

	// Detect cycle occurence by counting interations
	for (int i = 0; i < CYCLE_LIMIT; i++)
	{
		// If slot is empty then insert current key into 1st table
		if (array1_[arrayIndex1].isEmpty)
		{
			array1_[arrayIndex1].key = key;
			array1_[arrayIndex1].value = value;
			array1_[arrayIndex1].isEmpty = false;

			elements_++;
			return;
		}

		// If slot was occupied, insert current key into 1st table and keep old key
		std::swap(key, array1_[arrayIndex1].key);
		std::swap(value, array1_[arrayIndex1].value);

		arrayIndex2 = hash(key, 1);

		// Insert old key into 2nd array
		if (array2_[arrayIndex2].isEmpty)
		{
			array2_[arrayIndex2].key = key;
			array2_[arrayIndex2].value = value;
			array2_[arrayIndex2].isEmpty = false;

			elements_++;
			return;
		}

		// Again if slot was occupied, insert current key into 2nd table and keep old key
		std::swap(key, array2_[arrayIndex2].key);
		std::swap(value, array2_[arrayIndex2].value);
	}

	// If we come to this point then the cycle must have occured
	// To handle a cycle we perform rehashing and call insert for rehashed tables
	rehash();
	insert(key, value);
}

// Find if key is present in 1st or second table and remove it by reseting a node to default values
template <typename T1, typename T2>
void CuckooHashingTable<T1, T2>::remove(T1 key)
{
	int arrayIndex1 = hash(key, 0);
	int arrayIndex2 = hash(key, 1);

	
	if (array1_[arrayIndex1].isEmpty == false && array1_[arrayIndex1].key == key)
	{
		array1_[arrayIndex1].key = T1();
		array1_[arrayIndex1].value = T2();
		array1_[arrayIndex1].isEmpty = true;

		elements_--;

		return;
	}

	if (array2_[arrayIndex2].isEmpty == false && array2_[arrayIndex2].key == key)
	{
		array2_[arrayIndex2].key = T1();
		array2_[arrayIndex2].value = T2();
		array2_[arrayIndex2].isEmpty = true;

		elements_--;

		return;
	}
}

template <typename T1, typename T2>
size_t CuckooHashingTable<T1, T2>::calculateLoadFactor()
{
	loadFactor_ = elements_ / size_;
}

// Double the size and insert elements with new hash functions
template <typename T1, typename T2>
void CuckooHashingTable<T1, T2>::rehash()
{
	//std::cout << "rehash called\n";

	std::vector<Node<T1, T2>> temp1 = array1_;
	std::vector<Node<T1, T2>> temp2 = array2_;

	array1_.clear();
	array2_.clear();

	array1_.resize(size_ * 2);
	array2_.resize(size_ * 2);

	elements_ = 0;
	size_ *= 2;

	for (int i = 0; i < temp1.size(); i++)
	{
		if (!temp1[i].isEmpty)
		{
			insert(temp1[i].key, temp1[i].value);
		}
	}

	for (int i = 0; i < temp2.size(); i++)
	{
		if (!temp2[i].isEmpty)
		{
			insert(temp2[i].key, temp2[i].value);
		}
	}
}

// Display both tables
template <typename T1, typename T2>
void CuckooHashingTable<T1, T2>::display()
{
	std::cout << "Array 1 | Array 2\n";

	for (int i = 0; i < size_; i++)
	{
		if(array1_[i].isEmpty == false || array2_[i].isEmpty == false)
			std::cout << i << ": { " << array1_[i].key << ", " << array1_[i].value << " } { " << array2_[i].key << ", " << array2_[i].value << " }\n";
	}
}

#endif