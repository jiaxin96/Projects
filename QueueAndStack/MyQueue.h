//
// Created by rjx on 16-9-25.
//


#ifndef QUEUEANDSTACK_MYQUEUE_H
#define QUEUEANDSTACK_MYQUEUE_H
#define MAX_SIZE 200

#include <iostream>

template<class T>
class queue {
public:
    queue() {
        head = 0;
        rear = MAX_SIZE;
        count = 0;
    }

    size_t size() const {
        return count;
    }

    void push(T data) {
        if (!full()) {
            rear = (rear + 1) % (MAX_SIZE + 1);
            storage[rear] = data;
            count++;
        }
    }

    void pop() {
        if (!empty()) {
            count--;
            head = (head + 1) % (MAX_SIZE + 1);
        }
    }

    bool empty() const {
        return (((rear + 1) % (MAX_SIZE + 1)) == head);
    }

    bool full() const {
        return (((rear + 2) % (MAX_SIZE + 1)) == head);
    }

    T front() const {
        if (!empty())
            return storage[head];
    }

    T back() const {
        if (!empty())
            return storage[rear];
    }


private:
    T storage[MAX_SIZE + 1];
    size_t count;
    int head;
    int rear;
};
#endif //QUEUEANDSTACK_MYQUEUE_H
