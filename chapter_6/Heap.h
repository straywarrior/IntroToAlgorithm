/*
* The first index of element will be 1
*
*/

#ifndef _HEAP_H_
#define _HEAP_H_
#include <string.h>
#include <iostream>

class HeapOutOfBoundException : public std::exception{};

template <typename T>
class BaseHeap{
protected:
	T * A;
	int capacity;
	int size;
public:
	BaseHeap(int _Capacity) :capacity(_Capacity), size(0){
		A = new T[capacity + 1];
	}
	BaseHeap(T * src, int size) : capacity(size), size(size){
		A = new T[capacity + 1];
		memcpy((T *)A + 1, src, size * sizeof(T));
	}

	virtual int push(T val) = 0;
	virtual T pop() = 0;
	virtual void heapify(int i) = 0;

	void buildHeap();
	void print();

	inline int parent(int i){
		return (i >> 1);
	}
	inline int left(int i){
		return (i << 1);
	}
	inline int right(int i){
		return (i << 1) + 1;
	}
};


template <typename T>
class MaxHeap : public BaseHeap<T>{
public:
	MaxHeap(int _Capacity) :BaseHeap(_Capacity){}
	MaxHeap(T * src, int size) :BaseHeap(src, size){}
	int push(T val) override;
	T pop() override;
	virtual void heapify(int i) override;
};

template <typename T>
class MinHeap : public BaseHeap<T>{
public:
	MinHeap(int _Capacity) :BaseHeap(_Capacity){}
	MinHeap(T * src, int size) :BaseHeap(src, size){}
	int push(T val) override;
	T pop() override;
	virtual void heapify(int i) override;
};


template <typename T>
void BaseHeap<T>::print(){
	for (int i = 1; i <= size; i++)
		std::cout << A[i] << " ";
	std::cout << std::endl;
}

template <typename T>
void BaseHeap<T>::buildHeap(){
	for (int i = (size >> 1); i > 0; --i){
		heapify(i);
	}
}

template <typename T>
int MaxHeap<T>::push(T val){
	return 0;
}

template <typename T>
T MaxHeap<T>::pop(){
	return A[1];
}

template <typename T>
int MinHeap<T>::push(T val){
	return 0;
}
template <typename T>
T MinHeap<T>::pop(){
	return A[1];
}

template <typename T>
void MaxHeap<T>::heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int max;
	if (l > size && r > size)
		return;
	if ((l <= size) && (A[l] > A[i]))
		max = l;
	else
		max = i;
	if ((r <= size) && (A[r] > A[max]))
		max = r;
	if (max != i){
		T temp = A[i];
		A[i] = A[max];
		A[max] = temp;
		heapify(max);
	}
}

template <typename T>
void MinHeap<T>::heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int min;
	if (l > size && r > size)
		return;
	if ((l <= size) && (A[l] < A[i]))
		min = l;
	else
		min = i;
	if ((r <= size) && (A[r] < A[min]))
		min = r;
	if (min != i){
		T temp = A[i];
		A[i] = A[min];
		A[min] = temp;
		heapify(min);
	}
}
#endif