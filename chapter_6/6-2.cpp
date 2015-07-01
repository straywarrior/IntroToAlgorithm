/*
* Author : StrayWarrior
* Solution to 6.2-1, 6.2-2, 6.2-3, 6.5-3
* 
*/
#include <iostream>
#include "Heap.h"
#include <time.h>
#include "Task.h"


int ch6sec2()
{
	int n;
	std::cout << "Input the length of test case: " << std::endl;
	std::cin >> n;
	int * A = new int[n];
	srand(time(NULL));
	for (int i = 0; i < n; ++i){
		A[i] = rand();
	}
	MaxHeap<int, int, DummyKey<int, int>> heap_max(A, n);
	MinHeap<int> heap_min(A, n);
	for (int i = 0; i < n + 1; i++)
		heap_max.insertElem(rand());
	heap_max.buildHeap();
	heap_min.buildHeap();
	heap_max.printf();

	heap_max.changeKey(n >> 1, rand());
	heap_max.printf();

	heap_max.insertElem(rand());
	heap_max.printf();

	std::cout << "heap_max pop: " << heap_max.pop() << std::endl;
	heap_max.printf();

	heapSort(A, n);
	std::cout << "sorted A: ";
	for (int i = 0; i < n; ++i)
		std::cout << A[i] << " ";
	std::cout<<std::endl;

	Task task_arr[33];
	for (int i = 0; i < 33; ++i){
		task_arr[i] = Task(i, rand());
	}
	MaxHeap<Task, int, TaskKey> heap_task(task_arr, 33);
	heap_task.buildHeap();
	heap_task.print();

	return 0;
}
