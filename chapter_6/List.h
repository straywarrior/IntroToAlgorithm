#ifndef _LIST_H_
#define _LIST_H_ value
#include <iostream>

class ListOutOfBoundException :public std::exception{};

template <typename T>
class ListNode{
public:
	T val;
	ListNode* next = nullptr;
	ListNode(const T & val) :val(val){}
	ListNode(){}
	~ListNode(){
		next = nullptr;
	}
};

template <typename T>
class List{
public:
	int size = 0;
	ListNode<T> * head = nullptr; //the head node will never be deleted.
public:
	List() :head(new ListNode<T>()){}
	void insert(int i, const T& obj){
		if (size < i || i < 0)
			throw ListOutOfBoundException();
		ListNode<T> * curr = head;
		while (i--){
			curr = curr->next;
		}
		ListNode<T> * nodeNew = new ListNode<T>(obj);
		nodeNew->next = curr->next;
		curr->next = nodeNew;
		size++;
	}
	void insert(const T& obj){
		insert(0, obj);
	}
	T erase(int i){
		ListNode<T> * curr = head;
		while (i--){
			curr = curr->next;
		}
		T ret = curr->next->val;
		ListNode<T> * next = curr->next->next;
		delete curr->next;
		curr->next = next;
		size--;
		return ret;
	}
	void swap(const int & lhs, const int & rhs){
		if (lhs == rhs) return;
		int l(lhs), r(rhs);
		ListNode<T> * currLeft = head;
		ListNode<T> * currRight = head;
		ListNode<T> * tmp = nullptr;
		while (l--){
			currLeft = currLeft->next;
		}
		while (r--){
			currRight = currRight->next;
		}
		tmp = currLeft->next->next;
		currLeft->next->next = currRight->next->next;
		currRight->next->next = tmp;
		tmp = currLeft->next;
		currLeft->next = currRight->next;
		currRight->next = tmp;
	}
	T & front(){
		return head->next->val;
	}
	T & pop_front(){
		return erase(0);
	}
	T & pop_back(){
		return erase(size - 1);
	}

	void sort(int mode){ //Will be added later..
		switch (mode)
		{
		case 0: //Insert Sort
			break;
		default:
			break;
		}
	}
	void sort(){
		sort(0);
	}

};

#endif