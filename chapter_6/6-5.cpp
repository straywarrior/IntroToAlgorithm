#include <iostream>

#include "PriorityQueue.h"
#include "Task.h"

int ch6sec5(){
	PriorityQueue<Task, int, TaskKey> taskPQ_1(20);
	{
 		PriorityQueue<Task, int, TaskKey> taskPQ_2; 
	}

	for (int i = 0; i < 33; ++i){
		Task tmpTask(i, rand());
		taskPQ_1.push(tmpTask);
	}
	
	while (!taskPQ_1.empty()){
		std::cout << taskPQ_1.pop();
	}
	std::cout << std::endl;
	

	return 0;
}