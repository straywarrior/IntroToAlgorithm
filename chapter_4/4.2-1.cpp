/*
* Author : StrayWarrior
* Solution to 4.2-1, 4.2-2
* A lazy version using vector
* Note: the right edge points to the after-end of the index...
* ToDo: Add GC and fix the memory leak
*/
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Matrix.h"

Matrix::Matrix(int m, int n):m(m), n(n){
    ref_count = new int;
    *ref_count = 1;
    if (m * n == 0)
        return;
    A = new int * [m];
    for (int i = 0; i < m; ++i)
        A[i] = new int [n];
    //Initial it.
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j){
            A[i][j] = 0;
        }
    }
}
int * Matrix::operator[](int m) const{
        return A[m];
}

Matrix Matrix::operator()(int ms, int me, int ns, int ne) const{
    Matrix ret(me-ms, ne-ns);
    for(int i = 0; i < ret.m; ++i){
        for(int j = 0; j < ret.n; ++j){
            ret[i][j] = A[ms + i][ns + j];
        }
    }
    return ret;
}

Matrix::Matrix(const Matrix & src):Matrix(0, 0){
    *this = src;
}

Matrix & Matrix::operator=(const Matrix & src){
    if (this != &src){
        this->free();
        ref_count = src.ref_count;
        m = src.m;
        n = src.n;
        A = src.A;
        ++(*ref_count);
    }
    return *this; 
}

Matrix::Matrix(Matrix && src):Matrix(0, 0){
    *this = src;
}

Matrix & Matrix::operator=(Matrix && src){
    if (this != &src){
        this->free();
        memcpy(this, &src, sizeof(Matrix));
        ++(*ref_count);
    }
    return *this;
}

void Matrix::print() const{
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j){
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::free(){
    --(*ref_count);
    if (*ref_count == 0){
        for (int i = 0; i < m; ++i){
            delete [] A[i];
        }
        delete [] A;
        delete ref_count;
        ref_count = nullptr;
    }
}

Matrix::~Matrix(){
    this->free();
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs){
    if (lhs.m != rhs.m || lhs.n != rhs.n)
        exit(-1);
    Matrix sum(lhs.m, lhs.n);
    for (int i = 0; i < lhs.m; ++i){
        for (int j = 0; j < lhs.n; ++j)
            sum[i][j] = lhs[i][j] + rhs[i][j];
    }
    return sum;
}

Matrix combine_four(const Matrix &ltop, const Matrix &rtop, const Matrix &lbot, const Matrix &rbot){
    Matrix ret(ltop.m + lbot.m, ltop.n + rtop.n);
    for (int i = 0; i < ltop.m; i++){
        for (int j = 0; j < ltop.n; j++)
            ret[i][j] = ltop[i][j];
    }
    for (int i = 0; i < rtop.m; i++){
        for (int j = 0; j < rtop.n; j++)
            ret[i][j+ltop.n] = rtop[i][j];
    }
    for (int i = 0; i < lbot.m; i++){
        for (int j = 0; j < lbot.n; j++)
            ret[i+ltop.m][j] = lbot[i][j];
    }
    for (int i = 0; i < rbot.m; i++){
        for (int j = 0; j < rbot.n; j++)
            ret[i+ltop.m][j+ltop.n] = rbot[i][j];
    }
    return ret;
}

Matrix square_matrix_multiply_recursive(const Matrix & lhs, const Matrix & rhs){
    if (lhs.n != rhs.m)
        exit(-1);
    Matrix ret(lhs.m, rhs.n);
    if (lhs.m * lhs.n * rhs.n == 0)
        return ret;
    if (lhs.m == 1 && rhs.n ==1){
        for (int i = 0;i < lhs.n; ++i)
            ret[0][0] += lhs[0][i] * rhs[i][0];
        return ret;
    }
    int lm = lhs.m; int ln = lhs.n;
    int rm = rhs.m; int rn = rhs.n;
    Matrix C1(lm/2, rn/2), C2(lm/2, rn-rn/2), C3(lm-lm/2, rn/2), C4(lm-lm/2, rn-rn/2);
    
    C1 = square_matrix_multiply_recursive(lhs(0,lm/2,0,ln/2),rhs(0,rm/2,0,rn/2)) + square_matrix_multiply_recursive(lhs(0,lm/2,ln/2,ln), rhs(rm/2, rm, 0,rn/2));
    
    C2 = square_matrix_multiply_recursive(lhs(0,lm/2,0,ln/2), rhs(0,rm/2,rn/2,rn)) + square_matrix_multiply_recursive(lhs(0,lm/2,ln/2,ln), rhs(rm/2, rm, rn/2,rn));

    C3 = square_matrix_multiply_recursive(lhs(lm/2,lm,0,ln/2), rhs(0,rm/2,0,rn/2)) + square_matrix_multiply_recursive(lhs(lm/2,lm,ln/2,ln), rhs(rm/2, rm, 0,rn/2));

    C4 = square_matrix_multiply_recursive(lhs(lm/2,lm,0,ln/2), rhs(0,rm/2, rn/2,rn)) + square_matrix_multiply_recursive(lhs(lm/2,lm,ln/2,ln), rhs(rm/2, rm, rn/2,rn));

    ret = combine_four(C1, C2, C3, C4);
    return ret;
}

int main(){
//Scale of Matrix A;
    int Am, An;
    std::cout << "Input the scale of A: \n";
    std::cin >> Am >> An;
//Scale of Matrix B;
    int Bm, Bn;
    std::cout << "Input the scale of B: \n";
    std::cin >> Bm >> Bn;
    if (An != Bm){
        std::cout << "Error in the scale of matrix" << std::endl;
        return -1;
    }
    Matrix A(Am, An);
    Matrix B(Bm, Bn);
    for (int i = 0; i < Am; ++i){
        for (int j = 0; j < An; ++j)
            std::cin >> A[i][j];
    }
    for (int i = 0; i < Bm; ++i){
        for (int j = 0; j < Bn; ++j)
            std::cin >> B[i][j];
    }
    Matrix C = square_matrix_multiply_recursive(A, B);
    C.print();
    
    return 0;
}