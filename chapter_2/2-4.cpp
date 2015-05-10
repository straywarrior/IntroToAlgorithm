/*
* Author : StrayWarrior
* Solution to 2-4
* desc describes the numbers of inverted-sequence pair.
*/

#include <iostream>
static int desc = 0;

void merge(int * A, int lo, int mi, int hi);
void merge_sort(int * A, int lo, int hi);

void merge(int * A, int lo, int mi, int hi){
    int * B = new int[mi - lo];
    int * C = new int[hi - mi];
    
    for (int i = 0; i < mi - lo; ++i){
        B[i] = A[lo + i];
    }
    for (int i = 0; i < hi - mi; ++i){
        C[i] = A[mi + i];
    }
    int i = 0, j = 0;
    for (int k = lo;k < hi; ++k){
        if (i < mi - lo && (j == hi - mi || B[i] <= C[j]))
            A[k] = B[i++];
        else if (j < hi - mi && (i == mi - lo || C[j] < B[i])){
            A[k] = C[j++];
            desc += ((j-i > 0)?(mi - lo - i):0);
        }
    }
    delete [] B;
    delete [] C;
    return;
}

void merge_sort(int * A, int lo, int hi){
    if (hi - lo < 2) return;
    int mi = (lo + hi) >> 1;
    merge_sort(A, lo, mi);
    merge_sort(A, mi, hi);
    merge(A, lo, mi, hi);
    return;
}


int main(){
    int n;
    std::cout << "Input the Number of Array: " << std::endl;
    std::cin >> n;
    int * arr = new int[n];
    int i = 0;
    while (i < n){
        std::cin >> arr[i++];
    }
    merge_sort(arr, 0, n);
    for (int i = 0; i < n; ++i){
        std::cout << arr[i] << " ";
    }
    std::cout << "\n" << desc << std::endl;
}