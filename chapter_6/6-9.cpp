/*
* Author : StrayWarrior
* Solution to 6.5-9
* k-merge sort for k lists;
*/
#include "List.h"
#include "Heap.h"
#include <list>
#include <vector>
#include "Pair.h"
#include <time.h>

int ch6sec9(){
	int k(2);
	std::cin >> k;
	std::vector<std::list<int>> listVec(k);
	srand(time(NULL));
	for (int i = 0; i < k; i++){
		int size = rand() % 20;
		std::cout << "size " << i << ": " << size << std::endl;
		for (int j = 0; j < size; j++)
			listVec[i].push_front(rand());
		listVec[i].sort();
	}
	std::list<int> listSorted;
	MinHeap<std::pair<int, int>, int, PairKey<int ,int>> minHeap(k);
	for (int i = 0; i < k; ++i){
		minHeap.insertElem(std::pair<int, int>(listVec[i].front(), i));
		listVec[i].pop_front();
	}
	while (1){
		bool isFinished = true;
		for (int i = 0; i < k; ++i){
			isFinished &= listVec[i].empty();
		}
		if (isFinished) break;
		int nextList = (minHeap.top()).second;
		listSorted.push_back(minHeap.pop().first);
		if (!listVec[nextList].empty()){
			minHeap.insertElem(std::pair<int, int>(listVec[nextList].front(), nextList));
			listVec[nextList].pop_front();
		}
	}
	//Flush heap
	while (!minHeap.empty()){
		listSorted.push_back(minHeap.pop().first);
	}
	auto iter_beg = listSorted.begin();
	while (iter_beg != listSorted.end()){
		std::cout << *iter_beg++ << " ";
	}

	return 0;
}