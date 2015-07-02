#include "QuickSort.h"
#include <iostream>
#include <time.h>

int ch7sec1(){
	srand(time(NULL));
	for (int test_case = 0; test_case < 10; test_case++){
		int n = rand() % 100;
		int * A = new int[n];
		std::cout << "original array: ";
		for (int i = 0; i < n; ++i){
			A[i] = rand();
			std::cout << A[i] << " ";
		}
		std::cout << std::endl;
		quickSort(A, 0, n);
		std::cout << "sorted array: ";
		for (int i = 0; i < n; ++i){
			std::cout << A[i] << " ";
		}
		std::cout << std::endl;
		delete[] A;
	}
	
	return 0;
}