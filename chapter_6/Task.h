#ifndef _TASK_H_ 
#define _TASK_H_ value
class Task{
public:
	int id = 0;
	int priority = 0;
};

class TaskKey{
public:
	int& operator()(const Task & elem){
		return (int&)elem.id;
	}
};
#endif