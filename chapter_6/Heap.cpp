#include "Heap.h"

template <typename T>
void BaseHeap<T>::buildHeap(){
	for (int i = (size >> 1); i > 0; --i){
		heapify(i);
	}
}

template <typename T>
void MaxHeap<T>::heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int max;
	if (l <= size) && (A[l] > A[i])
		max = l;
	else
		max = i;
	if (r <= size) && (A[r] > A[i])
		max = r;
	if (max != i){
		T temp = A[i];
		A[i] = A[max];
		A[max] = temp;
	}
	heapify(max);
}

template <typename T>
void MinHeap<T>::heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int min;
	if (l <= size) && (A[l] < A[i])
		min = l;
	else
		min = i;
	if (r <= size) && (A[r] < A[i])
		min = r;
	if (min != i){
		T temp = A[i];
		A[i] = A[min];
		A[min] = temp;
	}
	heapify(min);
}