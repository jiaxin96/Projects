#include <iostream>
#include <string>

#include "../include/queue.hpp"

using namespace std;
Queue::Queue()
/* Post: The Queue is initialized to be empty.*/
{

	count = 0;
	rear = maxqueue - 1;
	front = 0;
}

bool Queue::empty()const
/* Post: Return true if the Queue is empty, otherwise return false.*/
{
	return count == 0;
}

Error_code Queue::append(const Queue_entry &item)
/* Post: item is added to the rear of the Queue. If the Queue is empty return an
         Error_code of underflow.*/
{
	if(count>=maxqueue)return overflow;
	count++;
	rear = ((rear+1)==maxqueue)?0:(rear+1);
	entry[rear]=item;
	return success;
}
Error_code Queue::apphead(const Queue_entry &item) {
	if(count>=maxqueue)return overflow;
	count++;
	rear = ((rear+1)==maxqueue)?0:(rear+1);
	for (int i = count - 1; i >= 1; --i) {
		int k = ((front + i) >= maxqueue) ? (front+i-maxqueue) : (front+i);
		int p = ((front + i - 1) >= maxqueue) ? (front+i - 1-maxqueue) : (front + i - 1);
		entry[k] = entry[p];
	}
	entry[front] = item;
	return success;
}

Error_code Queue::serve()
/*Post: The front of the Queue is removed. If the Queue is empty return an
        Error_code of underflow.*/
{
	if(count<=0)return underflow;
	count--;
	front = ((front+1)==maxqueue)?0:(front+1);
	return success;
}

Error_code Queue::retrieve(Queue_entry &item)const
/*Post: The front of the Queue retrieved to the output parameter item.
        If the Queue is empty return an Error_code of underflow.*/
{
	if(count<=0)return underflow;
	item=entry[front];
	return success;
}

int Queue::size() const {
	return count;
}

void Queue::sort() {
		for (int i = 0; i < count - 1; ++i) {
			for (int j = i + 1; j < count; ++j) {
				int p1 = ((front + i) >= maxqueue) ? (front+i-maxqueue) : (front+i);
				int p2 = ((front+j) >= maxqueue) ? (front+j-maxqueue) : (front+j);
				if (entry[p1].oil() > entry[p2].oil()) {
					Plane temp = entry[p1];
					entry[p1] = entry[p2];
					entry[p2] = temp;
				}
			}
		}
}

Queue_entry& Queue::nth_plane(int n) {
		if (n >= 0 && n < maxqueue) {
			int k = ((front + n) >= maxqueue) ? (front+n-maxqueue) : (front+n);
			return entry[k];
		}
}
