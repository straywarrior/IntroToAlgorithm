/*
* Author : StrayWarrior
* Solution to 6.2-1, 6.2-2, 6.2-3, 6.5-3, 6.5-8
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

template <typename T, typename KeyType = T>
class DummyKey{
public:
	KeyType& operator()(const T & elem){
		return (KeyType&)elem;
	}
};

template <typename T, typename KeyType = T, typename Key = DummyKey<T, KeyType>>
class LessCompareKey{
public:
	Key getKey;
	bool operator()(const T& lhs, const T& rhs){
		return (getKey(lhs) < getKey(rhs));
	}
};

template <typename T, typename KeyType = T, typename Key = DummyKey<T, KeyType>, typename CmpKey = LessCompareKey<T, KeyType, Key>>
class BaseHeap{
	template <typename T> friend void heapSort(T* src, int size);
protected:
	T * elems;
	Key getKey;
	CmpKey cmpKey;
public:
	int capacity;
	int size;

public:
	BaseHeap(int _Capacity) :capacity(_Capacity), size(0){
		elems = new T[capacity + 1];
	}
	BaseHeap(T * src, int size) : capacity(size << 1), size(size){
		elems = new T[capacity + 1];
		memcpy((T *)elems + 1, src, size * sizeof(T));
	}
	BaseHeap() :BaseHeap(20){}

	T top(){
		if (size)
			return elems[1];
		else
			throw HeapOutOfBoundException();
	}
	T pop(){
		if (size){
			T ret = elems[1];
			elems[1] = elems[size];
			size -= 1;
			heapify(1);
			return ret;
		}
		else
			throw HeapOutOfBoundException();
	}
	bool empty(){
		return (!(size > 0));
	}
	virtual void heapify(int i) = 0;
	virtual void changeKey(int i, const KeyType& newKey) = 0;
	void insertElem(const T& elem){
		if (size + 1 > capacity)
			expand();
		size += 1;
		//it's a hack;
		elems[size] = elem;
		if (size == 1) return;
		getKey(elems[size]) = getKey(elems[parent(size)]);
		changeKey(size, getKey(elem));
	}

	void deleteElem(int i){
		if (i > size)
			throw HeapOutOfBoundException();
		//is it safe to use std::swap?
		std::swap(elems[i], elems[size]);
		size -= 1;
		heapify(i);
	}

	void buildHeap(){
		for (int i = (size >> 1); i > 0; --i)
			heapify(i);
	}

	void print(){
		for (int i = 1; i <= size; i++)
			std::cout << elems[i] << " ";
		std::cout << std::endl;
	}
	void printf(){
		for (int i = 1; i <= exp2(round(log2(size))); i = i << 1){
			for (int j = i; j < (i << 1) && j <= size; j++)
				std::cout << elems[j] << " ";
			std::cout << std::endl;
		}
	}

protected:
	int expand(){
		capacity = capacity << 1;
		T* oldbuf = elems;
		elems = new T[capacity];
#if 1
		memcpy((T*)elems, (const T*)oldbuf, (size + 1)*sizeof(T));
		delete[] oldbuf;
#endif
		return capacity;
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

public:
	~BaseHeap(){
		delete[] elems;
	}
};


template <typename T, typename KeyType = T, typename Key = DummyKey<T, KeyType>>
class MaxHeap : public BaseHeap<T, KeyType, Key>{
public:
	MaxHeap(int _Capacity) :BaseHeap(_Capacity){}
	MaxHeap() : BaseHeap(){}
	MaxHeap(T * src, int size) :BaseHeap(src, size){}
	virtual void heapify(int i) override;
	virtual void changeKey(int i, const KeyType& newKey) override{
		if (i > size)
			throw HeapOutOfBoundException();
		KeyType & key = getKey(elems[i]);
		if (newKey < key){
			key = newKey;
			heapify(i);
		}
		else{
			key = newKey;
			while (i > 1 && cmpKey(elems[parent(i)], elems[i])){
				T tmp = elems[i];
				elems[i] = elems[parent(i)];
				elems[parent(i)] = tmp;
				i = parent(i);
			}
		}

	}
};

template <typename T, typename KeyType = T, typename Key = DummyKey<T, KeyType>>
class MinHeap : public BaseHeap<T, KeyType, Key>{
public:
	MinHeap(int _Capacity) :BaseHeap(_Capacity){}
	MinHeap() :BaseHeap(){}
	MinHeap(T * src, int size) :BaseHeap(src, size){}
	virtual void heapify(int i) override;
	virtual void changeKey(int i, const KeyType& newKey){
		if (i > size)
			throw HeapOutOfBoundException();
		KeyType & key = getKey(elems[i]);
		if (key < newKey){
			key = newKey;
			heapify(i);
		}
		else{
			key = newKey;
			while (i > 1 && cmpKey(elems[i], elems[parent(i)])){
				T tmp = elems[i];
				elems[i] = elems[parent(i)];
				elems[parent(i)] = tmp;
				i = parent(i);
			}
		}
		
	}
};


/*
* Old and Recursive Edition of Heapify-function(Temporarily not available in this version)
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
	if ((l <= size) && (elems[l] > elems[i])) //l is sure not greater than size..but isn't r
		max = l;
	else
		max = i;
	if ((r <= size) && (elems[r] > elems[max]))
		max = r;
	if (max != i){
		T temp = elems[i];
		elems[i] = elems[max];
		elems[max] = temp;
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
	if ((l <= size) && (elems[l] < elems[i]))
		min = l;
	else
		min = i;
	if ((r <= size) && (elems[r] < elems[min]))
		min = r;
	if (min != i){
		T temp = elems[i];
		elems[i] = elems[min];
		elems[min] = temp;
		heapify(min);
	}
}
#else

/*
* Iterative Edition of Heapify-function
*/

template <typename T, typename KeyType, typename Key>
void MaxHeap<T, KeyType, Key>::heapify(int i)
{
	int i_cur = i;
	int l, r, max;

	while (i_cur <= size >> 1){
		l = left(i_cur);
		r = right(i_cur);
		if (l > size && r > size)
			return;
		if (cmpKey(elems[i_cur], elems[l]))
			max = l;
		else
			max = i_cur;
		if (r <= size && cmpKey(elems[max], elems[r]))
			max = r;
		if (max != i_cur){
			T tmp = elems[i_cur];
			elems[i_cur] = elems[max];
			elems[max] = tmp;
			i_cur = max;
		}
		else{
			break;
		}
	}
}

template <typename T, typename KeyType, typename Key>
void MinHeap<T, KeyType, Key>::heapify(int i)
{
	int i_cur = i;
	int l, r, min;

	while (i_cur <= size >> 1){
		l = left(i_cur);
		r = right(i_cur);
		if (l > size && r > size)
			return;
		if (cmpKey(elems[l], elems[i_cur]))
			min = l;
		else
			min = i_cur;
		if (r <= size && cmpKey(elems[r], elems[min]))
			min = r;
		if (min != i_cur){
			T tmp = elems[i_cur];
			elems[i_cur] = elems[min];
			elems[min] = tmp;
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
		std::swap(tmpHeap.elems[1], tmpHeap.elems[i]);
		tmpHeap.size -= 1;
		tmpHeap.heapify(1);
	}
	memcpy((T*)src, (const T*)tmpHeap.elems + 1, size*sizeof(T));
}



#endif