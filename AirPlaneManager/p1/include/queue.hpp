#ifndef QUEUE_H
#define QUEUE_H
#include"Plane.hpp"
typedef Plane Queue_entry;   //定义飞机队列实体
const int maxqueue = 10;
enum Error_code{fail,success, overflow, underflow};  //注意‘失败’在后面才用到
class Queue{
public:
	Queue();
	bool empty()const;
	Error_code serve();
	Error_code append(const Queue_entry &item);
	Error_code retrieve(Queue_entry &item)const;
	int size() const;
protected:
	int count;
	int front, rear;
	Queue_entry entry[maxqueue];
};
#endif
