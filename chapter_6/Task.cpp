#include "Task.h"

std::ostream& operator << (std::ostream& out, Task& obj){
	out << "[" << obj.id << " " << obj.priority << "]";
	return out;
}