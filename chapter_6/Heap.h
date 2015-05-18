#include <exception>
class HeapOutOfBoundException : public std::exception{};

template <typename T>
class BaseHeap{
private:
	T * A;
	int capacity;
	int size;
public:
	BaseHeap(int _Capacity);

	virtual int push(T val) = 0;
	virtual T pop() = 0;

	T parent(int i){
		if (i < size)
			return A[i >> 1];
		else
			throw HeapOutOfBoundException();
	}
	T left(int i){
		if (2 * i < size)
			return A[i << 1];
		else
			throw HeapOutOfBoundException();
	}
	T right(int i){
		if (2 * i + 1 < size)
			return A[(i << 1) + 1];
		else
			throw HeapOutOfBoundException();
	}
};

template <typename T>
BaseHeap::BaseHeap(int _Capacity):capacity(_Capacity), size(0){
	A = new T[capacity];
}

template <typename T>
class MaxHeap : public BaseHeap<T>{
public:
	int push(T val) override;
	T pop() override;
	void maxHeapify(int i);
};

template <typename T>
class MinHeap : public BaseHeap<T>{
	int push(T val) override;
	T pop() override;
	void minHeapify(int i);
};