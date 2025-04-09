#ifndef CLOSED_ADDRESSING_TABLE_HPP
#define CLOSED_ADDRESSING_TABLE_HPP

#include "HashTable.hpp"
#include "SinglyLinkedList.hpp"

#include <vector>
#include <functional>
#include <cmath>

template <typename T1, typename T2>
class ClosedAddressingTable : public HashTable<T1, T2>
{
private:
	// Type definition for key - value buckets
	typedef SinglyLinkedList<T1, T2> Bucket;

	std::vector<Bucket> bucketArray_;
	size_t size_;
	size_t elements_;
	float loadFactor_;

	size_t hash(int key, int type = 0);
	size_t hash(float key, int type = 0);
	size_t hash(char key, int type = 0);
	size_t hash(std::string key, int type = 0);

public:
	ClosedAddressingTable(size_t size);
	ClosedAddressingTable(const ClosedAddressingTable<T1, T2>& copy);
	~ClosedAddressingTable();

	void insert(T1 key, T2 value) override;
	void remove(T1 key) override;
	void display();

	size_t calculateLoadFactor();
};

// Initialize empty table of specified size
template <typename T1, typename T2>
ClosedAddressingTable<T1, T2>::ClosedAddressingTable(size_t size) : size_(size), bucketArray_(size), elements_(0), loadFactor_(0.0)
{
	// In progress
}

// Copy constructor
template <typename T1, typename T2>
ClosedAddressingTable<T1, T2>::ClosedAddressingTable(const ClosedAddressingTable<T1, T2>& copy)
{
	bucketArray_ = copy.bucketArray_;
	size_ = copy.size_;
}

template <typename T1, typename T2>
ClosedAddressingTable<T1, T2>::~ClosedAddressingTable()
{
	// In progress
}

// Simple division based hash function
template <typename T1, typename T2>
size_t ClosedAddressingTable<T1, T2>::hash(int key, int type = 0)
{
	size_t hashValue = key % size_;

	return hashValue;
}

// hashing function using std::hash
template <typename T1, typename T2>
size_t ClosedAddressingTable<T1, T2>::hash(float key, int type = 0)
{
	std::hash<float> hashFunction;
	size_t hashValue = hashFunction(key);

	return hashValue;
}

// Simple division based hash function
template <typename T1, typename T2>
size_t ClosedAddressingTable<T1, T2>::hash(char key, int type = 0)
{
	char asciiValue = int(key);
	size_t hashValue = (asciiValue) % size_;

	return hashValue;
}
// Division based hash function
template <typename T1, typename T2>
size_t ClosedAddressingTable<T1, T2>::hash(std::string key, int type = 0)
{
	int sum = 0;

	// To get an integer value, we multiply every character of string by a large prime number
	for (int i = 0; i < key.size(); i++)
		sum += int(key[i]) * pow(31, i);

	size_t hashValue = sum % size_;

	return hashValue;
}

// Insert key-value pair at a calculated index and handle colission if it occurs
template <typename T1, typename T2>
void ClosedAddressingTable<T1, T2>::insert(T1 key, T2 value)
{
	int index = hash(key);
	bucketArray_[index].pushBack(key, value);

	elements_++;
}

// Find element with specified key and remove it
template <typename T1, typename T2>
void ClosedAddressingTable<T1, T2>::remove(T1 key)
{
	int index = hash(key);
	int pairToRemove = bucketArray_[index].find(key);

	bucketArray_[index].remove(pairToRemove);
}

template <typename T1, typename T2>
size_t ClosedAddressingTable<T1, T2>::calculateLoadFactor()
{
	loadFactor_ = elements_ / size_;
}

// Display every bucket
template <typename T1, typename T2>
void ClosedAddressingTable<T1, T2>::display()
{
	for (int i = 0; i < size_; i++)
	{
		if(!bucketArray_[i].isEmpty())
			bucketArray_[i].show();
	}
}
#endif