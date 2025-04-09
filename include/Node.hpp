#ifndef NODE_HPP
#define NODE_HPP

template <typename T1, typename T2>
struct Node
{
	T1 key;
	T2 value;
	bool isEmpty;

	Node(): key(T1()), value(T2()), isEmpty(true) {}
};

#endif