#ifndef _TASK_H_ 
#define _TASK_H_ value
#include <iostream>

class Task{
public:
	friend std::ostream& operator << (std::ostream& out, Task& obj);
	int id = 0;
	int priority = 0;

	Task(int id, int prio) :id(id), priority(prio){}
	Task() :Task(0, 0){}
	
};

class TaskKey{
public:
	int& operator()(const Task & elem){
		return (int&)elem.priority;
	}
};

std::ostream& operator << (std::ostream& out, Task& obj){
	out << "[" << obj.id << " " << obj.priority << "]";
	return out;
}

#endif