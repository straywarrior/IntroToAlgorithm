#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_ value

#include "Heap.h"
class PQueueOuOfBoundException :public HeapOutOfBoundException{};

template <typename T, typename KeyType = T, typename Key = DummyKey<T, KeyType>>
class PriorityQueue{
protected:
	MaxHeap<T, KeyType, Key> buf;
public:
	PriorityQueue(const int & capacity) :buf(MaxHeap<T, KeyType, Key>(capacity)){
	}
	PriorityQueue() :PriorityQueue(20){}
	bool empty(){
		return buf.empty();
	}
	T & top(){
		try{
			return buf.top();
		}
		catch (HeapOutOfBoundException e){
			throw PQueueOuOfBoundException();
		}
	}
	T pop(){
		try{
			return buf.pop();
		}
		catch (HeapOutOfBoundException e)
		{
			throw PQueueOuOfBoundException();
		}
	}
	void push(const T & obj){
		buf.insertElem(obj);
	}
};

#endif