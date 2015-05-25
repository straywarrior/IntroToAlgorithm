/*
* Author : StrayWarrior
* Solution to 6.2-1, 6.2-2
* 
*/
#include <iostream>
#include "Heap.h"
#include <time.h>

int main()
{
	int n;
	std::cout << "Input the number of test case: " << std::endl;
	std::cin >> n;
	int * A = new int[n];
	srand(time(NULL));
	for (int i = 0; i < n; ++i){
		A[i] = rand();
	}
	MaxHeap<int> heap_max(A, n);
	MinHeap<int> heap_min(A, n);
	heap_max.buildHeap();
	heap_max.print();
	
	return 0;
}
