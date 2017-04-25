#include <iostream>
#include "MyQueue.h"
#include "MyStack.h"

using namespace std;

template<class T>
bool Sdo(stack<T> & s) {
    cout << "1.push 2.pop 3.top 4.size 5.exit\n";
    int p;
    cout << "Your option:";
    cin >> p;
    switch (p) {
        case 1:
            T data;
            cout << "input your data:";
            cin >> data;
            s.push(data);
            return true;
        case 2:
            if (!s.empty())
                s.pop();
            else
                cout << "Stack is empty!\n";
            return true;
        case 3:
            if (!s.empty()) {
                cout << "Stack's top is " << s.top() << endl;
            } else {
                cout << "Stack is empty!\n";
            }
            return true;
        case 4:
            cout << "Stack's size is " << s.size() << endl;
            return true;
        case 5:
            return false;
        default:
            cout << "Input incorrectly\n";
    }
    return true;
}

template<class T>
bool Qdo(queue<T> & q) {
    cout << "1.push 2.pop 3.front 4.back 5.size 6.exit\n";
    int p;
    cout << "Your option:";
    cin >> p;
    switch (p) {
        case 1:
            T data;
            cout << "input your data:";
            cin >> data;
            q.push(data);
            return true;
        case 2:
            if (!q.empty())
                q.pop();
            else
                cout << "Stack is empty!\n";
            return true;
        case 3:
            if (!q.empty()) {
                cout << "Queue's top is " << q.front() << endl;
            } else {
                cout << "Queue is empty!\n";
            }
            return true;
        case 4:
            if (!q.empty()) {
                cout << "Queue's back is " << q.back() << endl;
            } else {
                cout << "Queue is empty!\n";
            }
            return true;
        case 5:
            cout << "Queue's size is " << q.size() << endl;
            return true;
        case 6:
            return false;
        default:
            cout << "Input incorrectly\n";
    }
    return true;
}


template<class T>
void test() {
    stack<T> s;
    queue<T> q;
    cout << "Test Stack\n";
    {
        int t;
        cout << "Input test case times\n";
        cin >> t;
        while (t--) {
            cout << "in put you operation\n";
            while (Sdo<T>(s));
        }
    }
    cout << "Test Queue\n";
    {
        int t;
        cout << "Input test case times\n";
        cin >> t;
        while (t--) {
            cout << "in put you operation\n";
            while (Qdo<T>(q));
        }
    }
}

int main() {
    test<char>();
    return 0;
}