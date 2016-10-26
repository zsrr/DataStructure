#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#define CANNOT_BE_FOUND -1

#include "LinearList.h"
#include "../MyOwnException.h"

template<class T>
struct ChainNode {
	T element;
	ChainNode<T>* next;

	ChainNode(const T& theElement) {
		element = theElement;
		next = nullptr;
	}

	ChainNode(const T& theElement, ChainNode<T>* next) {
		element = theElement;
		this->next = next;
	}
};

template<class T>
class LinkedList : LinearList<T> {
public:
	LinkedList() = default;
	LinkedList(const LinkedList<T>& list);
	int getSize() const override { return listSize; }
	T& get(int index) const override;
	int indexOf(const T& element) const override;
	void erase(int index) override;
	void insert(int index, const T& element) override;
	void sort(int(*func)(T, T) = nullptr) override;
	void push_back(const T& element) override;
	void push_front(const T& element);
	~LinkedList();
private:
	int listSize = 0;
	ChainNode<T>* firstNode = nullptr;
	void checkIndex(int index) const throw(IndexOutOfBounds);
	void checkParameter(int parameter) const throw(IllegalParameterValue);
};

#endif // !LINKED_LIST_H

template<class T>
inline void LinkedList<T>::checkIndex(int index) const throw(IndexOutOfBounds) {
	if (index < 0 || index >= listSize) {
		throw IndexOutOfBounds();
	}
}

template<class T>
inline void LinkedList<T>::checkParameter(int parameter) const throw(IllegalParameterValue) {
	if (parameter <= 0) {
		throw IllegalParameterValue();
	}
}

template<class T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& list) {
	if (list.listSize == 0) {
		listSize = 0;
		firstNode = nullptr;
		return;
	}

	listSize = list.listSize;

	firstNode = new ChainNode<T>(list.firstNode->element);
	ChainNode<T>* targetNode = firstNode->next;
	ChainNode<T>* sourceNode = list.firstNode->next;
	while (sourceNode != nullptr) {
		targetNode = new ChainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
}

template<class T>
inline T & LinkedList<T>::get(int index) const {
	checkIndex(index);
	ChainNode<T>* temp = firstNode;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return temp->element;
}

template<class T>
inline int LinkedList<T>::indexOf(const T & element) const {
	ChainNode<T>* temp = firstNode;
	for (int i = 0; i < listSize; i++) {
		if (temp->element == element) {
			return i;
		}
		temp = temp->next;
	}

	return CANNOT_BE_FOUND;
}

template<class T>
inline void LinkedList<T>::erase(int index) {
	checkIndex(index);

	if (index == 0) {
		ChainNode<T>* temp = firstNode->next;
		delete firstNode;
		firstNode = temp;
		listSize--;
		return;
	}

	ChainNode<T>* temp = firstNode;
	for (int i = 0; i < index - 1; i++) {
		temp = temp->next;
	}
	ChainNode<T>* nextTemp = temp->next;
	temp->next = nextTemp->next;
	delete nextTemp;
	listSize--;
}

template<class T>
inline void LinkedList<T>::insert(int index, const T & element) {
	checkIndex(index);

	if (index == 0) {
		firstNode = new ChainNode<T>(element, firstNode);
		listSize++;
		return;
	}

	ChainNode<T>* temp = firstNode;
	for (int i = 0; i < index - 1; i++) {
		temp = temp->next;
	}
	temp->next = new ChainNode<T>(element, temp->next);
	listSize++;
}

template<class T>
inline void LinkedList<T>::sort(int(*func)(T, T)) {
}

template<class T>
inline void LinkedList<T>::push_back(const T & element) {
	if (listSize == 0) {
		firstNode = new ChainNode<T>(element);
		listSize++;
		return;
	}

	ChainNode<T>* temp = firstNode;
	for (int i = 0; i < listSize - 1; i++) {
		temp = temp->next;
	}
	temp->next = new ChainNode<T>(element);
	listSize++;
}

template<class T>
inline void LinkedList<T>::push_front(const T & element) {
	firstNode = new ChainNode<T>(element, firstNode);
	listSize++;
}

template<class T>
inline LinkedList<T>::~LinkedList() {
	while (firstNode != nullptr) {
		ChainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}
