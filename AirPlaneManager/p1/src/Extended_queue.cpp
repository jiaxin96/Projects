#include<iostream>
#include"Extended_queue.hpp"
int Extended_queue::size()const
{
	return count;
}
bool Extended_queue::full()const
{
	return count==maxqueue;
}
void Extended_queue::clear()
{
	count=0;
	front=0;
	rear=maxqueue-1;
}
Error_code Extended_queue::serve_and_retrieve(Queue_entry &item)
{
	if(count==0)return underflow;
	else{
		count--;
		item=entry[front];
		front=((front+1)==maxqueue)?0:(front+1);
	}
	return success;
}
