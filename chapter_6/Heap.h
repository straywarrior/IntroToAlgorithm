/*
* Author : StrayWarrior
* Solution to 6.2-1, 6.2-2, 6.2-3, 6.5-3
* Note: The first index of elements in Heap-in array will be 1
*
*/

#ifndef _HEAP_H_
#define _HEAP_H_ value
#include <string.h>
#include <iostream>
#include <math.h>

//#define _HEAP_HEAPIFY_RECUR_

class HeapOutOfBoundException : public std::exception{};

template <typename T>
class DummyKey{
public:
	T& operator()(const T & elem){
		return (T&)elem;
	}
};

template <typename T, typename Key = DummyKey<T>>
class LessCompareKey{
public:
	Key getKey;
	bool operator()(const T& lhs, const T& rhs){
		return (getKey(lhs) < getKey(rhs));
	}
};

template <typename T, typename Key = DummyKey<T>, typename CmpKey = LessCompareKey<T, Key>>
class BaseHeap{
	template <typename T> friend void heapSort(T* src, int size);
protected:
	T * A;
	Key getKey;
	CmpKey cmpKey;
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

	T top(){
		if (size)
			return A[1];
		else
			throw HeapOutOfBoundException();
	}
	T pop(){
		if (size){
			T ret = A[1];
			A[1] = A[size];
			size -= 1;
			heapify(1);
			return ret;
		}
		else
			throw HeapOutOfBoundException();
	}
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
	~BaseHeap(){
		delete[] A;
	}
};


template <typename T, typename Key = DummyKey<T>>
class MaxHeap : public BaseHeap<T, Key>{
public:
	MaxHeap(int _Capacity) :BaseHeap(_Capacity){}
	MaxHeap(T * src, int size) :BaseHeap(src, size){}
	virtual void heapify(int i) override;
};

template <typename T, typename Key = DummyKey<T>>
class MinHeap : public BaseHeap<T, Key>{
public:
	MinHeap(int _Capacity) :BaseHeap(_Capacity){}
	MinHeap(T * src, int size) :BaseHeap(src, size){}
	virtual void heapify(int i) override;
};


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

template <typename T, typename Key>
void MaxHeap<T, Key>::heapify(int i)
{
	int i_cur = i;
	int l, r, max;

	while (i_cur <= size >> 1){
		l = left(i_cur);
		r = right(i_cur);
		if (l > size && r > size)
			return;
		if (cmpKey(A[i_cur], A[l]))
			max = l;
		else
			max = i_cur;
		if (r <= size && cmpKey(A[max], A[r]))
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

template <typename T, typename Key>
void MinHeap<T, Key>::heapify(int i)
{
	int i_cur = i;
	int l, r, min;

	while (i_cur <= size >> 1){
		l = left(i_cur);
		r = right(i_cur);
		if (l > size && r > size)
			return;
		if (cmpKey(A[l], A[i_cur]))
			min = l;
		else
			min = i_cur;
		if (r <= size && cmpKey(A[r], A[min]))
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

/* Algorithm related to Heap */
template <typename T>
void heapSort(T* src, int size){
	MaxHeap<T> tmpHeap(src, size);
	tmpHeap.buildHeap();
	for (int i = tmpHeap.size; i > 1; i--){
		std::swap(tmpHeap.A[1], tmpHeap.A[i]);
		tmpHeap.size -= 1;
		tmpHeap.heapify(1);
	}
	memcpy((T*)src, (const T*)tmpHeap.A + 1, size*sizeof(T));
}



#endif