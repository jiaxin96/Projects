#ifndef EXTENDED_QUEUE_HPP_
#define EXTENDED_QUEUE_HPP_
#include"queue.hpp"
#include"Plane.hpp"
typedef Plane Queue_entry;//飞机队列实体
class Extended_queue:public Queue {  //对队列公有继承
public:
	bool full()const;
	int size()const;
	void clear();
	Error_code serve_and_retrieve(Queue_entry &item);
/*
private:
	int count;
	int front;
	int rear;
	Queue_entry entry[maxqueue];
*/
};
#endif
