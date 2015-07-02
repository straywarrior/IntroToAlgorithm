#include "QuickSort.h"
#include <utility>

void quickSort(int * A, const int & p, const int & r){
	if (p < r - 1){
		int q = partion(A, p, r);
		quickSort(A, p, q);
		quickSort(A, q + 1, r);
	}
}

int partion(int * A, const int & p, const int & r){
	int pivotVal = A[r - 1];
	int i = p - 1;
	for (int j = p; j < r - 1; j++){
		if (A[j] < pivotVal){
			i += 1;
			std::swap(A[i], A[j]);
		}
	}
	std::swap(A[++i], A[r - 1]);
	return i;
}
