/*
 * author: sofowora
 */
 //  LinkedList.h
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <memory>
#include <string>
#include <initializer_list>
#include <fstream>
//////////////////////////////////////----------------------------#pragma once

// Requirements:
// Class template>>
// No STL containers>>
// Smart pointers>>
// Copy and move constructors
// Assignment and move operators
// Method for adding an element>>
// Method for searching an element>>
// Method for sorting (in case of sequential data structures)>>
// Method for (de) serialization (transformation from and to a binary stream)
// Implementation of an iterator (optional task)//

template <typename T>
class ListNode
{
private:
	T _value;
	std::shared_ptr<ListNode<T>> _next{};
	std::weak_ptr<ListNode<T>> _prev{};
	friend LinkedList<T>;

public:
	ListNode(const T&);
	ListNode<T>& operator=(const T&);
	ListNode<T>& operator=(const ListNode<T>&);
	ListNode<T>& operator=(const ListNode<T>*);
	template <typename U>
	friend std::ostream& operator<<(std::ostream&, const LinkedList<U>&);

	// 	template <typename U>
	// 	friend std::ostream &operator<<(std::ostream &, const ListNode<U> &);
};

template <typename T>
class LinkedList
{
private:
	std::shared_ptr<ListNode<T>> _head{ NULL }, _tail{ NULL };
	size_t _size{};
	int data;

public:
	LinkedList();												  // constructor
	~LinkedList();												  // destructor
	LinkedList(const LinkedList<T>& otherList);					  // copy constructor
	void copyList(const LinkedList<T>& otherList);				  // copy constructor 2 copy list
	LinkedList(LinkedList<T>&& otherList);						  // move constructor to create
	const LinkedList& operator=(const LinkedList<T>& otherList);  // copy assignment operator
	const LinkedList& operator=(const LinkedList<T>&& otherList); // move assignment operator

	LinkedList(const std::initializer_list<T>&); // initializer
	size_t size() const;						  // check size of the list
	bool isEmpty() const;						  // check if list is empty
	bool contains(const T&) const;
	void add(const T&&);						   // add to list
	void add(size_t, const T&);				   // maybe add to node
	void addAll(const std::initializer_list<T>&); // add to all
	bool remove(const T&);
	T get(size_t) const;					 // get funct
	T set(size_t, const T&);				 // set funct
	T remove(size_t);						 // remover from list
	void clear();							 // clear from list
	size_t indexOf(const T&) const;		 // get index
	void printAll();						 // print list
	bool search(ListNode<T>* head, int x);	 // search through list
	void sort();							 // sort list
	bool swap(size_t index1, size_t index2); // swap indexes
	int length(ListNode<T>* head);			 // get length
	void readfile(std::string filename);	 // serialiation
	ListNode<T>& operator[](size_t) const;
	template <typename U>
	friend std::ostream& operator<<(std::ostream&, const LinkedList<U>&); // friend output stream
																			// void serialization(const std::string &file_name);
																			// void desrialization(const std::string &file_name);
};
/** A special type for results. */
enum params_result
{
	PARAMS_OK,	 ///< program called correctly
	PARAMS_HELP, ///< help called
	PARAMS_ERROR ///< incorrect parameters of program call
};
/*
================================= Realization of class ListNode =================================
*/
template <typename T>
ListNode<T>::ListNode(const T& value) : _value(value) {}

template <typename T>
std::ostream& operator<<(std::ostream& out, const ListNode<T>& element)
{
	out << element._value;
	return out;
}
// copy constructor 1
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherlist)
{
	cout << "Copy constructor allocating ptr." << endl;
	LinkedNode<T> list1 = NULL; // current
	std::unique_ptr<LinkedList<T>> list2 = NULL;
	if (otherlist._head == NULL)
		_head = NULL;
	else
	{
		_head = new LinkedNode<T>(otherlist._head->_value);
		_head->_value = otherlist._head->_value;
		_head->info = otherlist._head->_value;
		list1 = _head;
		list2 = otherlist._head->_next;
	}
	while (list2)
	{
		list1->_next = new LinkedNode<T>;
		list1 = list1->_next;
		list1->_value = list2->_value;
		list1->info = list2->info;
		list2 = list2->_next;
	}
	list1->_next = NULL;
}
// copy constructor 2
template <typename T>
void LinkedList<T>::copyList(const LinkedList<T>& otherList) // copy constructor
{
	cout << "Copy constructor allocating ptr." << endl;
	size_t count;
	LinkedNode<T>* newNode = new LinkedNode<T>; // pointer to create a node
	LinkedNode<T>* current;						// pointer to traverse the list

	if (otherList._head == NULL) // otherList is empty
	{
		_head = NULL;
		_tail = NULL;
		count = 0;
	}
	else
	{
		current = otherList._head;	   // current points to the list to be copied
		count = otherList.count;	   // copy the first node
		_head = new LinkedNode<T>;	   // create the node
		_head->info = current->info;   // copy the info
		_head->_next = current->_next; // set the link field of the node to NULL
		_head->_prev = current->_prev;

		_tail = _head; // make last point to the first node

		current = current->_next; // make current point to the next node
		// copy the remaining list

		while (current != NULL)
		{
			newNode = new LinkedNode<T>;   // create a node
			newNode->info = current->info; // copy the info
			newNode->_next = current->_next;
			newNode->_prev = current->_prev;
			_tail->_next = newNode;
			_tail = newNode;
			current = current->_next;
		}
	}
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& otherlist) noexcept // move constructor
{
	if (&otherlist != this)
	{
		_size = otherlist._size;
		otherlist._size = 0;
		_head = otherlist._head;
		otherlist._head = nullptr;
		_tail = otherlist._tail;
		otherlist._tail = nullptr; // to avoid self copying

		LinkedNode<T>* head = otherlist._head;
		LinkedNode<T>* headNext = otherlist._head->_next;
		for (size_t i = 0; i < otherlist._size - 1; i++)
		{
			head = nullptr;
			head = headNext;
			headNext = headNext->_next;
		}
		otherlist._size = 0;
	}
}

template <typename T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& otherlist)
{
	if (this != &otherist) // avoid self-copy
	{
		copyList(otherList);
	} // end else
	else
	{
		_size = otherlist._size;
		delete[] _head; // Delete the old buffer of the destination
		_head = new int[_size + 1];
		copyList(_head, otherlist._head);
		return *this;
	}
	return *this;
}

template <typename T>
const LinkedList<T>::& LinkedList<T>::& operator=(const LinkedList<T>&& otherList) noexcept
{
	s = std::move(otherlist->s); // something like that
	if (this != &otherlist)
	{
		_size = otherlist._size;
		_head = otherlist._head;
		_tail = otherlist._tail;
		otherlist._head = nullptr;
		otherlist._size = 0;
		otherlist._tail = nullptr; // to avoid self copying
	}

	swap(*this, otherlist);
	return (*this);
}

template <typename T>
ListNode<T>& ListNode<T>::operator=(const T& value)
{
	_value = value;
	return *this;
}
template <typename T>
ListNode<T>& ListNode<T>::operator=(const ListNode<T>& element)
{
	_value = element._value;
	return *this;
}
template <typename T>
ListNode<T>& ListNode<T>::operator=(const ListNode<T>* element)
{
	_value = element->_value;
	return *this;
}
/*
================================= Realization of class LinkedList =================================
*/
template <typename T>
LinkedList<T>::LinkedList() : _size(0) {}
template <typename T>
LinkedList<T>::~LinkedList()
{
}
template <typename T>
LinkedList<T>::LinkedList(const std::initializer_list<T>& elements)
{
	for (T element : elements)
		add(element);
}
template <typename T>
size_t LinkedList<T>::size() const
{
	return _size;
}
template <typename T>
bool LinkedList<T>::isEmpty() const
{
	return _size == 0;
}
template <typename T>
bool LinkedList<T>::contains(const T& value) const
{
	ListNode<T>* node = _head;
	while (node != NULL)
	{
		if (node->_value != value)
			node = node->_next;
		else
			return true;
	}
	return false;
}
template <typename T>
void LinkedList<T>::add(const T&& value)
{
	ListNode<T>* newElement = std::make_shared<ListNode<T>>(value);
	if (_size != 0)
	{
		_tail->_next = newElement;
		newElement->_prev = _tail;
		_tail = newElement;
	}
	else
	{
		_head = newElement;
		_tail = newElement;
	}
	++_size;
}
template <typename T>
void LinkedList<T>::add(size_t index, const T& value)
{
	if (_size == 0)
	{
		add(value);
		return;
	}
	if (index >= 0 && index < _size)
	{
		auto node = _head;
		for (size_t i = 0; i < index; ++i)
			node = node->_next;
		ListNode<T>* newElement = std::make_shared<ListNode<T>>(value);
		newElement._next = node;
		newElement._prev = node->_prev;
		if (node->_prev != NULL)
			node->_prev->_next = newElement;
		node->_prev = newElement;
		if (index == 0)
			_head = newElement;
		if (index == _size - 1)
			_tail = newElement->_next;
		++_size;
	}
	else
		throw std::out_of_range("LinkedList :: add(index, value)");
}
template <typename T>
void LinkedList<T>::addAll(const std::initializer_list<T>& elements)
{
	for (T element : elements)
		add(element);
}
template <typename T>
bool LinkedList<T>::remove(const T& value)
{
	ListNode<T>* node = _head;
	bool isDeleted = false;
	while (node != NULL)
	{
		if (node->_value != value)
			node = node->_next;
		else
		{
			if (node->_prev != nullptr)
				node->_prev->_next = node->_next;
			if (node->_next != nullptr)
				node->_next->_prev = node->_prev;
			if (_tail == node && node->_prev != nullptr)
				_tail = node->_prev;
			if (_head == node && node->_next != nullptr)
				_head = node->_next;
			if (_head == _tail && _tail == node)
				_head = _tail = nullptr;
			LinkedNode<T>* tmp = node->_next;
			node->_next = nullptr;
			node->_prev = nullptr;
			node = tmp;
			tmp = nullptr;
			--_size;
			isDeleted = true;
		}
	}
	return isDeleted;
}
template <typename T>
T LinkedList<T>::remove(size_t index)
{
	if (index >= 0 && index < _size)
	{
		ListNode<T>* node = _head;
		for (size_t i = 0; i < index; ++i)
			node = node->_next;
		if (node->_prev != NULL)
			node->_prev->_next = node->_next;
		if (node->_next != NULL)
			node->_next->_prev = node->_prev;
		if (_tail == node && node->_prev != NULL)
			_tail = node->_prev;
		if (_head == node && node->_next != NULL)
			_head = node->_next;
		if (_head == _tail && _tail == node)
			_head = _tail = NULL;
		node->_next = NULL;
		node->_prev = NULL;
		--_size;
		return node->_value;
	}
	else
		throw std::out_of_range("LinkedList :: remove(index)");
}
template <typename T>
void LinkedList<T>::clear()
{
	if (_size != 0)
	{
		ListNode<T>* node = _tail.get();
		while (node != NULL)
		{
			if (node->_next != NULL)
			{
				node->_next = NULL;
			}
			if (node->_prev != NULL)
				node = node->_prev.get();
			else
			{
				delete node;
				node = NULL;
			}
		}
		_head = _tail = NULL;
		_size = 0;
	}
}
template <typename T>
T LinkedList<T>::get(size_t index) const
{
	if (index >= 0 && index < _size)
	{
		ListNode<T>* node = _head;
		for (size_t i = 0; i < index; ++i)
			node = node->_next;
		return node->_value;
	}
	else
		throw std::out_of_range("LinkedList :: get(index)");
}
template <typename T>
T LinkedList<T>::set(size_t index, const T& value)
{
	if (index >= 0 && index < _size)
	{
		ListNode<T>* node = _head;
		for (size_t i = 0; i < index; ++i)
			node = node->_next;
		T tmp = node->_value;
		node->_value = value;
		return tmp;
	}
	else
		throw std::out_of_range("LinkedList :: set(index, value)");
}
/*--------------------------- TODO:----------------------------------- */
template <typename T>
size_t LinkedList<T>::indexOf(const T& element) const
{
	ListNode<T>* tempNode = _head;
	size_t count = 0;
	while (tempNode != NULL)
	{
		if (element.compare(tempNode->element) == 0)
		{
			return count;
		}
		++count;
		tempNode = tempNode->next;
	}
	return -1;
}
// go throught the list and return number of element visited,
template <typename T>
bool LinkedList<T>::search(ListNode<T>* head, int x)
{
	// Base case
	if (head == NULL)
		return false;

	// If key is present in current node, return true
	if (head->data == x)
		return true;

	// Recur for remaining list
	return search(head->next, x);
}
template <typename T>
bool LinkedList<T>::swap(size_t index1, size_t index2)
{
	if (index1 >= 0 && index1 < _size && index2 >= 0 && index2 < _size)
	{
		ListNode<T>* tmp = (*this)[index1];
		(*this)[index1] = (*this)[index2];
		(*this)[index2] = tmp;
		return true;
	}
	else
		return false;
}
template <typename T>
size_t LinkedList<T>::length(ListNode<T>* head)
{
	LinkedNode<T>* tmp = _head;
	size_t i = 0;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->_next;
	}

	return i;
}
// Bubble sort the given linked list
template <typename T>
void LinkedList<T>::bubbleSort(ListNode<T>* head)
{
	size_t swapp, i;
	ListNode<T>(*this)[index1];
	ListNode<T>(*this)[index2] = NULL;

	/* Checking for empty list */
	if (head == NULL)
		return;

	do
	{
		swapp = 0;
		(*this)[index1] = _head;

		while ((*this)[index1]->_next != (*this)[index1])
		{
			if ((*this)[index1]->data > (*this)[index1]->_next->data)
			{
				swap((*this)[index1], (*this)[index1]->)_next);
				swapp = 1;
			}
			(*this)[index1] = (*this)[index1]->_next;
		}
		(*this)[indexlast] = (*this)[index1];
	} while (swapp);
}
// bubble sort, two loops inside another
// serialization of the list
template <typename T>
void LinkedList<T>::printAll(std::ostream& os)
{
	if (head == NULL)
	{
		os << "There are no nodes in the list" << endl;
		return;
	}
	else
	{
		ListNode<T>* tmp = head;
		os << endl
			<< "RUID    Name" << endl;

		while (tmp != NULL)
		{
			os << tmp->ID << "\t" << tmp->name << endl;
			tmp = tmp->next;
		}
	}
	os << endl;
}
// read file
template <typename T>
void LinkedList<T>::readfile(string filename)
{
	ifstream file;
	file.open(filename);
	string line;

	if (file)
	{
		getline(file, line);
		cout << line << endl;
	}
	file.close();
}
// read data
template <typename T>
void LinkedList<T>::saveData(LinkedList<T>* p_list_ptr)
{
	fstream file("data.bin", ios::out | ios::binary);

	file.seekp(0);
	file.write((char*)p_list_ptr, sizeof(*p_list_ptr));
	file.close();
}
// load data
template <typename T>
void LinkedList<T>::loadData(LinkedList<T>* p_list_ptr)
{
	fstream file("data.bin", ios::in | ios::binary);

	file.seekg(0);
	file.read((char*)p_list_ptr, sizeof(*p_list_ptr));
	file.close();
}
// operator index
template <typename T>
ListNode<T>& LinkedList<T>::operator[](size_t index) const
{
	if (index >= 0 && index < _size)
	{
		ListNode<T>* node = _head;
		for (size_t i = 0; i < index; ++i)
			node = node->_next;
		return *node;
	}
	else
		throw std::out_of_range("LinkedList :: operator [index]");
}
// output operator
template <typename T>
friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list)
{
	ListNode<T>* node = list._head.get();
	os << '[';
	while (node != NULL)
	{
		if (node->_next != NULL)
			os << node->_value << ", ";
		else
			os << node->_value;
		node = node->_next.get();
	}
	os << ']\n';
	node = NULL;
	return os;
}

#endif
