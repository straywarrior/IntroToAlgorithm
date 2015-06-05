/*
* The first index of element will be 1
*
*/

#ifndef _HEAP_H_
#define _HEAP_H_
#include <string.h>
#include <iostream>
#include <math.h>

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

	void buildHeap(){
		for (int i = (size >> 1); i > 0; --i)
			heapify(i);
	}
	void print(){
		for (int i = 1; i <= size; i++)
			std::cout << A[i] << " ";
		std::cout << std::endl;
	}
	void printf(){
		for (int i = 1; i <= exp2(round(log2(size))); i = i << 1){
			for (int j = i; j < (i << 1) && j <= size; j++)
				std::cout << A[j] << " ";
			std::cout << std::endl;
		}
	}

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


/*
* Recursive Edition of Heapify-function
*/
#ifdef _HEAP_HEAPIFY_RECUR_
template <typename T>
void MaxHeap<T>::heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int max;
	if (l > size && r > size)
		return;
	if ((l <= size) && (A[l] > A[i])) //l is sure not greater than size..but isn't r
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
#else

/*
* Iterative Edition of Heapify-function
*/

template <typename T>
void MaxHeap<T>::heapify(int i)
{
	int i_cur = i;
	int l, r, max;

	while (i_cur <= size >> 1){
		l = left(i_cur);
		r = right(i_cur);
		if (l > size && r > size)
			return;
		if (A[l] > A[i_cur])
			max = l;
		else
			max = i_cur;
		if (r <= size && A[r] > A[max])
			max = r;
		if (max != i_cur){
			T tmp = A[i_cur];
			A[i_cur] = A[max];
			A[max] = tmp;
			i_cur = max;
		}
		else{
			break;
		}
	}
}

template <typename T>
void MinHeap<T>::heapify(int i)
{
	int i_cur = i;
	int l, r, min;

	while (i_cur <= size >> 1){
		l = left(i_cur);
		r = right(i_cur);
		if (l > size && r > size)
			return;
		if (A[l] < A[i_cur])
			min = l;
		else
			min = i_cur;
		if (r <= size && A[r] < A[min])
			min = r;
		if (min != i_cur){
			T tmp = A[i_cur];
			A[i_cur] = A[min];
			A[min] = tmp;
			i_cur = min;
		}
		else{
			break;
		}
	}
}

#endif





#endif