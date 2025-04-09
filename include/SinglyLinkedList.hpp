	
#ifndef SINGLY_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_HPP

#include <iostream>
#include <fstream>
#include <sstream>

template  <typename T1, typename T2>
class SinglyNode
{
private:
	T1 key_;
	T2 value_;
	SinglyNode<T1, T2>* next_;
	template  <typename T1, typename T2> friend class SinglyLinkedList;
};

template  <typename T1, typename T2>
class SinglyLinkedList
{
private:
	SinglyNode<T1, T2>* head_;
	SinglyNode<T1, T2>* tail_;
	int size_;

	bool success_ = 1;

public:
	SinglyLinkedList();
	~SinglyLinkedList();

	void pushBack(const T1& key, const T2& value);
	void pushFront(const T1& key, const T2& value);
	void insert(const T1& key, const T2& value, const int& index);

	// TODO: Prohibit user from removing a node from an empty list
	void popBack();
	void popFront();
	void remove(const int& index);

	T2 getValue(const int& index);
	int getSize() const;
	void show() const;
	bool isEmpty() const;
	int find(const T1& key) const;
};


// Create an empty list
template  <typename T1, typename T2>
SinglyLinkedList<T1, T2>::SinglyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

template  <typename T1, typename T2>
SinglyLinkedList<T1, T2>::~SinglyLinkedList()
{
	while (!isEmpty())
		popFront();
}

template  <typename T1, typename T2>
bool SinglyLinkedList<T1, T2>::isEmpty() const
{
	if (head_ == nullptr && tail_ == nullptr)
		return true;
	return false;
}

template  <typename T1, typename T2>
int SinglyLinkedList<T1, T2>::getSize() const
{
	return size_;
}

// Add element to the front of the list
template  <typename T1, typename T2>
void SinglyLinkedList<T1, T2>::pushFront(const T1& key, const T2& value)
{
	SinglyNode<T1, T2>* node = new SinglyNode<T1, T2>;

	node->value_ = value;
	node->key_ = key;
	node->next_ = head_;

	if (this->isEmpty())
	{
		tail_ = node;
	}

	head_ = node;

	size_ += 1;
}

// Add element to the back of the list
template  <typename T1, typename T2>
void SinglyLinkedList<T1, T2>::pushBack(const T1& key, const T2& value)
{
	if (this->isEmpty())
	{
		this->pushFront(key, value);
	}

	else
	{
		SinglyNode<T1, T2>* node = new SinglyNode<T1, T2>;

		node->value_ = value;
		node->key_ = key;
		node->next_ = nullptr;

		tail_->next_ = node;
		tail_ = node;

		size_ += 1;
	}
}

// Add element at specifed index
template  <typename T1, typename T2>
void SinglyLinkedList<T1, T2>::insert(const T1& key, const T2& value, const int& index)
{
	// Handle index out of range
	if (index < 0 || index >= size_)
	{
		std::cerr << "error: index out of range\n";
		this->success_ = 0;
		return;
	}

	if (index == 0)
		this->pushFront(value);

	else
	{
		SinglyNode<T1, T2>* current_node = head_;
		SinglyNode<T1, T2>* new_node = new SinglyNode<T1, T2>;

		// get to the element at index-1 position
		for (int i = 0; i < index - 1; i++)
			current_node = current_node->next_;

		new_node->value_ = value;
		new_node->key_ = key;

		new_node->next_ = current_node->next_;
		current_node->next_ = new_node;

		size_ += 1;
	}
}

// delete first element
template  <typename T1, typename T2>
void SinglyLinkedList<T1, T2>::popFront()
{
	if (this->isEmpty())
	{
		std::cerr << "error: list is empty\n";
		this->success_ = 0;
		return;
	}

	SinglyNode<T1, T2>* temporary_node = head_;
	head_ = temporary_node->next_;

	if (head_ == nullptr)
		tail_ = temporary_node->next_;

	delete temporary_node;
	size_ -= 1;
}

// delete last element
template  <typename T1, typename T2>
void SinglyLinkedList<T1, T2>::popBack()
{
	if (this->isEmpty())
	{
		std::cerr << "error: list is empty";
		this->success_ = 0;
		return;
	}

	if (head_->next_ == nullptr)
		this->popFront();

	else
	{
		SinglyNode<T1, T2>* current_node = head_;
		SinglyNode<T1, T2>* temporary_node = tail_;

		int index = size_ - 2;

		for (int i = 0; i < index; i++)
			current_node = current_node->next_;

		current_node->next_ = nullptr;
		tail_ = current_node;

		delete temporary_node;
		size_ -= 1;
	}
}

// delete element at index
template  <typename T1, typename T2>
void SinglyLinkedList<T1, T2>::remove(const int& index)
{
	// Handle index out of range
	if (index < 0 || index >= size_)
	{
		std::cerr << "error: index out of range\n";
		this->success_ = 0;
		return;
	}

	if (this->isEmpty())
	{
		std::cerr << "error: list is empty";
		this->success_ = 0;
		return;
	}

	if (index == 0)
		this->popFront();

	else if (index == size_ - 1)
		this->popBack();

	else
	{
		SinglyNode<T1, T2>* current_node = head_;
		SinglyNode<T1, T2>* temporary_node = nullptr;

		for (int i = 0; i < index - 1; i++)
			current_node = current_node->next_;

		temporary_node = current_node->next_;
		current_node->next_ = current_node->next_->next_;

		delete temporary_node;
		size_ -= 1;
	}
}

// get element at index
template  <typename T1, typename T2>
T2 SinglyLinkedList<T1, T2>::getValue(const int& index)
{
	// Handle index out of range
	if (index < 0 || index >= size_)
	{
		std::cerr << "error: index out of range\n";
		this->success_ = 0;
		return T{};
	}

	if (index == 0)
		return this->head_->value_;

	else if (index == size_ - 1)
		return this->tail_->value_;

	SinglyNode<T1, T2>* current_node = head_;

	for (int i = 0; i < index; i++)
		current_node = current_node->next_;

	return current_node->value_;
}

// Display entire list in a user friendly format
template  <typename T1, typename T2>
void SinglyLinkedList<T1, T2>::show() const
{
	SinglyNode<T1, T2>* current_node = head_;

	while (current_node != nullptr)
	{
		std::cout << "{ " << current_node->key_ << ", " << current_node->value_ << " } -> ";
		current_node = current_node->next_;
	}

	std::cout << '\n';
}

// Return an index of a first occurence of a specified value. In case of failure return -1
template  <typename T1, typename T2>
int SinglyLinkedList<T1, T2>::find(const T1& key) const
{
	SinglyNode<T1, T2>* current_node = head_;
	int index = 0;

	while (current_node != nullptr)
	{
		if (current_node->key_ == key)
			return index;

		current_node = current_node->next_;

		index++;
	}

	return -1;
}

#endif