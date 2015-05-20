#include <exception>
/*
* The first index of element will be 1
*
*/

class HeapOutOfBoundException : public std::exception{};

template <typename T>
class BaseHeap{
private:
	T * A;
	int capacity;
	int size;
public:
	BaseHeap(int _Capacity);
	BaseHeap(T * src, int size);

	virtual int push(T val) = 0;
	virtual T pop() = 0;
	virtual heapify(int i) = 0;

	void buildHeap();

	inline int parent(int i){
		return (i >> 1)
	}
	inline int left(int i){
		return (i << 1);
	}
	inline int right(int i){
		return (i << 1) + 1;
	}
};

template <typename T>
BaseHeap<T>::BaseHeap(int _Capacity):capacity(_Capacity), size(0){
	A = new T[capacity + 1];
}

template <typename T>
BaseHeap<T>::BaseHeap(T * src, int size):capacity(size), size(size){
	A = new T[capacity + 1];

}


template <typename T>
class MaxHeap : public BaseHeap<T>{
public:
	int push(T val) override;
	T pop() override;
	void heapify(int i) override;
};

template <typename T>
class MinHeap : public BaseHeap<T>{
	int push(T val) override;
	T pop() override;
	void heapify(int i) override;
};