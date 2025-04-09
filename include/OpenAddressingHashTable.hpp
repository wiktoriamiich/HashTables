#ifndef OPENHASH_TABLE_HPP
#define OPENHASH_TABLE_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

#include "HashTable.hpp"

// Define a template class for open addressing hash table
template <typename T1, typename T2>
class OpenAddressingTable : public HashTable<T1,T2> {

private:
// Define a structure to represent each entry in the hash table
	struct HashEntry {
		T1 key;
		T2 value;
		bool isDeleted;
		bool isOccupied;

		// Constructor to initialize entry flags
		HashEntry() : isDeleted(false), isOccupied(false) {}
	};
	
	std::vector<HashEntry> table;		// Vector to hold hash table entries
	int size;				// Current number of elements in the table
	int capacity;				// Total capacity of the table

	// Private member function to calculate hash value for a given key
	int hash(const T1& key);


public:
	OpenAddressingTable(int tableSize);				// Constructor
	OpenAddressingTable(const OpenAddressingTable<T1,T2>& copy);	// Copy constructor
	~OpenAddressingTable();						// Destructor
	void insert(T1 key, T2 value) override;				// Function to insert a key-value pair
	void remove(T1 key) override;					// Function to remove a key-value pair
	T2 search(T1 key);						// Function to search for a value associated with a key
};

// Implementation of hash function
template <typename T1, typename T2>
int OpenAddressingTable<T1,T2>::hash(const T1& key) {
	std::hash<T1> hashFunction;
	return hashFunction(key) % capacity;
}

// Constructor
template <typename T1, typename T2>
OpenAddressingTable<T1,T2>::OpenAddressingTable(int tableSize): size(0), capacity(tableSize) {
	table.resize(tableSize);
}

// Copy constructor
template <typename T1, typename T2>
OpenAddressingTable<T1, T2>::OpenAddressingTable(const OpenAddressingTable<T1, T2>& copy)
{
	this->size = copy.size;
	this->capacity = copy.capacity;
	this->table = copy.table;
}


// Destructor
template <typename T1, typename T2>
OpenAddressingTable<T1,T2>::~OpenAddressingTable() {
	table.clear();
}

// Function to insert a key-value pair into the hash table
template <typename T1, typename T2>
void OpenAddressingTable<T1,T2>::insert(T1 key, T2 value) {
	// Check if the table is full
	if (size == capacity) {
		throw std::out_of_range("Table is full");
	}
	
	int index = hash(key);		// Calculate the hash value for the key
	int start_index = index;

	// Linear probing to find an empty slot or a slot with deleted entry
	while (table[index].isOccupied && !table[index].isDeleted) {
		// Check if the key already exists
		if (table[index].key == key )
			{
			throw std::invalid_argument("Key already exists");
		}
		index = (index + 1) % capacity;		// Move to the next slot
		// Check if we have traversed the entire table without finding an empty slot
		if (index == start_index) {
			throw std::out_of_range("Table is full");
		}
	}
	// Insert the key-value pair into the table
	table[index].key = key;
	table[index].value = value;
	table[index].isOccupied = true;
	table[index].isDeleted = false;
	// Increment the size of the table
	size++;

	//std::cout << "inserted key" << key << " at index " << index << "\n";
}

// Function to remove a key-value pair from the hash table
template <typename T1, typename T2>
void OpenAddressingTable<T1,T2>::remove(T1 key) {
	int index = hash(key);		// Calculate the hash value for the key
	int start_index = index;

	// Linear probing to find the key
	while (table[index].isOccupied) {
		 // Check if the current entry matches the key and is not marked as deleted
		if (table[index].key == key && !table[index].isDeleted) {
			table[index].isDeleted = true;		// Mark the entry as deleted
			//std::cout << "Removed key: " << key << " from index: " << index << "\n";
			// Decrement the size of the table
			size--;
			return;
		}
		index = (index + 1) % capacity;		// Move to the next slot
		 // Check if we have traversed the entire table without finding the key
		if (index == start_index) {
			break;
		}
	}

	// Key not found
	throw std::out_of_range("Key not found");
}

// Function to search for a value associated with a key in the hash table
template <typename T1, typename T2>
T2 OpenAddressingTable<T1,T2>::search(T1 key) {
	// Calculate the hash value for the key
	int index = hash(key);
	int start_index = index;

	// Linear probing to find the key
	while (table[index].isOccupied) {
		// Check if the current entry matches the key and is not marked as deleted
		if (table[index].key == key && !table[index].isDeleted) {
			//std::cout << "Found key: " << key << " at index: " << index << "\n";
			// Return the value associated with the key
			return table[index].value;
		}
		index = (index + 1) % capacity;		// Move to the next slot
		// Check if we have traversed the entire table without finding the key
		if (index == start_index) {
			throw std::out_of_range("Key not found");
			break;
		}
	}

	// Key not found
	throw std::out_of_range("Key not found");
}

#endif //OPENHASH_TABLE_HPP
