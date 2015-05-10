/*
* Author : StrayWarrior
* Solution to 4.1-3
* desc describes the numbers of inverted-sequence pair.
*/
#include <iostream>

class SubArray {
public:
    int lo;
    int hi;
    int sum;
    SubArray();
    SubArray(int _lo, int _hi, int _sum);
};

SubArray::SubArray(int _lo, int _hi, int _sum):lo(_lo), hi(_hi), sum(_sum){}
SubArray::SubArray():SubArray(-1, 0, 0){}

bool operator<(const SubArray & lhs, const SubArray & rhs){
    return lhs.sum < rhs.sum;
}

bool operator<=(const SubArray & lhs, const SubArray & rhs){
    return lhs.sum <= rhs.sum;
}

SubArray find_max_cross_subarr(int * A, int lo, int mi ,int hi);
SubArray find_max_subarr(int * A, int lo, int hi);

SubArray find_max_cross_subarr(int * A, int lo, int mi, int hi){
    SubArray ret;
    int left_sum = -1, right_sum = -1;
    int sum = 0;
    for (int i = mi - 1; i >= lo; --i){
        sum += A[i];
        if (sum > left_sum){
            left_sum = sum;
            ret.lo = i;
        }
    }
    sum = 0;
    for (int i = mi; i < hi; ++i){
        sum += A[i];
        if (sum > right_sum){
            right_sum = sum;
            ret.hi = i;
        }
    }
    ret.sum = left_sum + right_sum;
    return ret;
}

SubArray find_max_subarr(int * A, int lo, int hi){
    SubArray ret;
    SubArray left_array, right_array, cross_array;
    if (hi == lo + 1){
        ret = SubArray(lo, hi, A[lo]);
        return ret;
    }
    if (hi == lo){
        return SubArray(-1, 0, 0);
    }
    int mi = (lo + hi) >> 1;
    left_array = find_max_subarr(A, lo, mi);
    right_array = find_max_subarr(A, mi, hi);
    cross_array = find_max_cross_subarr(A, lo, mi, hi);
    if (right_array <= left_array && cross_array <= left_array)
        return left_array;
    else if(left_array <= right_array && cross_array <= right_array)
        return right_array;
    else
        return cross_array;
}


int main()
{
    int n;
    std::cout << "Input the size of Array: " << std::endl;
    std::cin >> n;
    int * A = new int[n];
    std::cout << "Input the members of Array: " << std::endl;
    for (int i = 0; i < n; ++i)
        std::cin >> A[i];
    SubArray ret;
    ret = find_max_subarr(A, 0, n);
    std::cout << ret.lo << " " << ret.hi << " " << ret.sum << std::endl;
    
    return 0;
}
