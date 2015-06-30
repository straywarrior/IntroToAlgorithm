/*
* Author : StrayWarrior
* Solution to 6.2-1, 6.2-2, 6.2-3
* 
*/
#include <iostream>
#include "Heap.h"
#include <time.h>


int main()
{
	int n;
	std::cout << "Input the length of test case: " << std::endl;
	std::cin >> n;
	int * A = new int[n];
	srand(time(NULL));
	for (int i = 0; i < n; ++i){
		A[i] = rand();
	}
	MaxHeap<int> heap_max(A, n);
	MinHeap<int> heap_min(A, n);
	heap_max.buildHeap();
	heap_min.buildHeap();
	std::cout << heap_max.pop() << std::endl;

	heap_max.print();
	heapSort(A, n);
	for (int i = 0; i < n; ++i)
		std::cout << A[i] << " ";
	std::cout<<std::endl;
	
	return 0;
}
