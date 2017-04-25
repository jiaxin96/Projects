//
// Created by rjx on 16-9-25.
//

#ifndef QUEUEANDSTACK_MYSTACK_H
#define QUEUEANDSTACK_MYSTACK_H
#define MAX_SIZE 200

#include <iostream>
template<class T>
class stack {
public:
    stack() {
        count = 0;
    }
    ~stack() {
        while (!empty()) {
            pop();
        }
    }
    void push(T data) {
        if (count == 0) {
            storage = new node(data);
        } else {
            node *temp = new node(data, storage);
            storage = temp;
        }
        count++;
    }

    void pop() {
        if (!empty()) {
            node *temp = storage->next;
            delete storage;
            storage = temp;
            count--;
        }
    }

    size_t size() const {
        return count;
    }

    T top() const {
        if (!empty()) {
            return storage->data;
        }
    }

    bool empty() const {
        return (count == 0);
    }

    bool full() const {
        return (count == MAX_SIZE);
    }
private:
    struct node {
        T data;
        node *next;

        node(T d, node *n = NULL) : data(d), next(n) {}
    };
    node *storage;
    size_t count;
};

#endif //QUEUEANDSTACK_MYSTACK_H
