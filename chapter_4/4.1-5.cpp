/*
* Author : StrayWarrior
* Solution to 4.1-5
* An O(n) algorithm for the largest subarray problem.
*/
#include <iostream>

int main(){
    int n;
    std::cin >> n;
    int * A = new int[n];
    for (int i = 0; i < n; ++i)
        std::cin >> A[i];
    int lo(-1), hi(0), cur_lo(0);
    int max_sum(0), cur_sum(0);
    for (int i = 0; i < n; ++i){
        cur_sum += A[i];
        if (cur_sum > max_sum){
            lo = cur_lo;
            hi = i + 1;
            max_sum = cur_sum;
        }
        if (cur_sum < 0){
            cur_sum = 0;
            cur_lo = i + 1;
        }
    }
    std::cout << lo << " " << hi << " " << max_sum << std::endl;
}