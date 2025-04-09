#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <string>
#include <vector>

#include "HashTable.hpp"

using namespace std;

// Structure defining a node in the AVL tree
template <typename T1, typename T2>
struct AVLNode {
	T1 key;
	T2 value;
	AVLNode<T1, T2>* left;
	AVLNode<T1, T2>* right;
	int height;

	// Constructor
	AVLNode(T1 key, T2 value) : key(key), value(value), left(nullptr), right(nullptr), height(1) {};
};

// AVL tree class
template <typename T1, typename T2>
class AVL : public HashTable<T1,T2>{
private:
	AVLNode<T1,T2>* root;

	int height(AVLNode<T1, T2>* node);
	int balanceFactor(AVLNode<T1, T2>* node);
	void updateHeight(AVLNode<T1, T2>* node);
	AVLNode<T1, T2>* rotateRight(AVLNode<T1, T2>* node);
	AVLNode<T1, T2>* rotateLeft(AVLNode<T1, T2>* node);
	AVLNode<T1, T2>* balance(AVLNode<T1, T2>* node);
	AVLNode<T1, T2>* insert(AVLNode<T1, T2>* node, T1 key, T2 value);
	AVLNode<T1, T2>* findMin(AVLNode<T1, T2>* node);
	AVLNode<T1, T2>* removeMin(AVLNode<T1, T2>* node);
	AVLNode<T1, T2>* remove(AVLNode<T1, T2>* node, T1 key);
	AVLNode<T1,T2>* search(AVLNode<T1, T2>* node, T1 key);

public:
	// Constructor and Destructor
	AVL(int size);
	AVL(const AVL& other);
	~AVL();

	void insert(T1 key, T2 value) override;
	void remove(T1 key) override;
	T2 search(T1 key);
};

// Function to calculate the height of a node
template<typename T1, typename T2>
int AVL<T1, T2>::height(AVLNode<T1, T2>* node) {
	// Returns the height of the node if it exists, otherwise returns 0
	return node ? node->height : 0;
}

// Function to calculate the balance factor of a node
template<typename T1, typename T2>
int AVL<T1, T2>::balanceFactor(AVLNode<T1, T2>* node) {
	// Returns the balance factor of the node
	return height(node->right) - height(node->left);
}

// Function to update the height of a node
template<typename T1, typename T2>
void AVL<T1, T2>::updateHeight(AVLNode<T1, T2>* node) {
	// Height of the left subtree
	int hl = height(node->left);
	
	 // Height of the right subtree
	int hr = height(node->right);
	
	// Updates the height of the node
	node->height = (hl > hr ? hl : hr) + 1;
}

// Function to perform a right rotation
template<typename T1, typename T2>
AVLNode<T1, T2>* AVL<T1, T2>::rotateRight(AVLNode<T1, T2>* node) {
	AVLNode<T1, T2>* left = node->left;
	node->left = left->right;
	left->right = node;
	updateHeight(node);
	updateHeight(left);
	// Returns the new root after rotation
	return left;
}

// Function to perform a left rotation
template<typename T1, typename T2>
AVLNode<T1, T2>* AVL<T1, T2>::rotateLeft(AVLNode<T1, T2>* node) {
	AVLNode<T1, T2>* right = node->right;
	node->right = right->left;
	right->left = node;
	updateHeight(node);
	updateHeight(right);
	// Returns the new root after rotation
	return right;
}

// Function to balance a node
template<typename T1, typename T2>
AVLNode<T1, T2>* AVL<T1, T2>::balance(AVLNode<T1, T2>* node) {
	// Update the height of the node
	updateHeight(node);
	if (balanceFactor(node) == 2)
	// Right heavy
	{
		if (balanceFactor(node->right) < 0)
		// Right-Left case{
			// Right rotate the right child
			node->right = rotateRight(node->right);
		}
		// Left rotate the node
		return rotateLeft(node);
	}
	if (balanceFactor(node) == -2) 
	// Left heavy
	{
		// Left-Right case
		if (balanceFactor(node->left) > 0) {
			// Left rotate the left child
			node->left = rotateLeft(node->left);
		}
		// Right rotate the node
		return rotateRight(node);
	}
	// No rotation needed
	return node;
}

// Function to insert a key-value pair into the AVL tree
template<typename T1, typename T2>
AVLNode<T1, T2>* AVL<T1, T2>::insert(AVLNode<T1, T2>* node, T1 key, T2 value) {
	if (!node) {
		// Create a new node if the node is null
		return new AVLNode<T1, T2>(key, value);
	}
	if (key < node->key) {
		// Insert into the left subtree if key is smaller
		node->left = insert(node->left, key, value);
	}
	else if (key > node->key) {
		// Insert into the right subtree if key is larger
		node->right = insert(node->right, key, value);
	}
	else {
		// If the key already exists, return the node
		return node;
	}
	// Balance the node after insertion
	return balance(node);
}

// Function to find the minimum key node in the AVL tree
template<typename T1, typename T2>
AVLNode<T1, T2>* AVL<T1, T2>::findMin(AVLNode<T1, T2>* node) {
	// Recursively find the leftmost node
	return node->left ? findMin(node->left) : node;
}

// Function to remove the node with the minimum key in the AVL tree
template<typename T1, typename T2>
AVLNode<T1, T2>* AVL<T1, T2>::removeMin(AVLNode<T1, T2>* node) {
	if (!node->left) {
		// If the left child is null, return the right child
		return node->right;
	}
	// Recursively remove the minimum node
	node->left = removeMin(node->left);
	// Balance the node after removal
	return balance(node);
}

// Function to remove a key-value pair from the AVL tree
template<typename T1, typename T2>
AVLNode<T1, T2>* AVL<T1, T2>::remove(AVLNode<T1, T2>* node, T1 key) {
	if (!node) {
		// Return null if the node is null
		return nullptr;
	}
	if (key < node->key) {
		// Remove from the left subtree if key is smaller
		node->left = remove(node->left, key);
	}
	else if (key > node->key) {
		// Remove from the right subtree if key is larger
		node->right = remove(node->right, key);
	}
	else {
		AVLNode<T1, T2>* left = node->left;
		AVLNode<T1, T2>* right = node->right;
		// Delete the node
		delete node;
		if (!right) {
			// If right child is null, return left child
			return left;
		}
		// Find the minimum node in the right subtree
		AVLNode<T1, T2>* min = findMin(right);
		
		// Remove the minimum node
		min->right = removeMin(right);
		
		// Update left child
		min->left = left;
		
		// Balance the node after removal
		return balance(min);
	}
	// Balance the node after removal
	return balance(node);
}

// Function to search for a key in the AVL tree
template<typename T1, typename T2>
AVLNode<T1, T2>* AVL<T1, T2>::search(AVLNode<T1, T2>* node, T1 key) {
	if (!node) {
		// Return null if the node is null
		return nullptr;
	}
	if (key < node->key) {
		// Search in the left subtree if key is smaller
		return search(node->left, key);
	}
	else if (key > node->key) {
		// Search in the right subtree if key is larger
		return search(node->right, key);
	}
	else {
		// Return the node if key is found
		return node;
	}
}

// Constructor
template<typename T1, typename T2>
AVL<T1, T2>::AVL(int size) {
	for (int i = 0; i < size; i++) {
		// Insert default key-value pairs into the AVL tree
		insert(T1(), T2());
	}
}

// Copy constructor
template <typename T1, typename T2>
AVL<T1, T2>::AVL(const AVL& other) {
	// Initialize a stack to perform a depth-first traversal of the other AVL tree
	vector<AVLNode<T1, T2>*> stack;

	// Start traversal from the root of the other AVL tree
	stack.push_back(other.root);

	 // Traverse the other AVL tree using a depth-first approach
	while (!stack.empty()) {
		// Retrieve the current node from the stack
		AVLNode<T1, T2>* node = stack.back();
		// Remove the current node from the stack
		stack.pop_back();

		// If the current node has a left child, add it to the stack for traversal
		if (node->left) {
			stack.push_back(node->left);
		}
		// If the current node has a right child, add it to the stack for traversal
		if (node->right) {
			stack.push_back(node->right);
		}
		// Insert the key-value pair of the current node into the new AVL tree being constructed
		insert(node->key, node->value);
	}
}

// Destructor
template<typename T1, typename T2>
AVL<T1, T2>::~AVL() {
	vector<AVLNode<T1, T2>*> stack;
	stack.push_back(root);
	while (!stack.empty()) {
		AVLNode<T1, T2>* node = stack.back();
		stack.pop_back();
		if (node->left) {
			stack.push_back(node->left);
		}
		if (node->right) {
			stack.push_back(node->right);
		}
		// Delete each node
		delete node;
	}
}

// Function to insert a key-value pair into the AVL tree
template<typename T1, typename T2>
void AVL<T1, T2>::insert(T1 key, T2 value) {
	// Insert into the AVL tree
	root = insert(root, key, value);
}

// Function to remove a key-value pair from the AVL tree
template<typename T1, typename T2>
void AVL<T1, T2>::remove(T1 key) {
	// Remove from the AVL tree
	root = remove(root, key);
}

// Function to search for a key in the AVL tree
template<typename T1, typename T2>
T2 AVL<T1, T2>::search(T1 key) {
	// Search for the key in the AVL tree
	AVLNode<T1, T2>* node = search(root, key);
	if (node) {
		// If key is found, return its value
		return node->value;
	}

	// If key is not found, throw an exception
	throw std::out_of_range("Key not found");
}

#endif //!AVL_HPP
