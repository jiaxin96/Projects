#include <iostream>

template<class T>
class ListedList {
public:
    ListedList() {
        count = 0;
        head = new node(0);
    }

    ListedList(ListedList<T> &ot) {
        ot.count = count;
        ot.head = new node(0);
        node *temp = ot.head;
        node *trv = head;
        for (int i = 0; i < count; ++i) {
            temp->next = new node(trv->next->data);
            temp = temp->next;
            trv = trv->next;
        }
    }

    bool insert(int pos, T data) {
        if (pos < 0 || pos > count) return false;
        if (pos == 0) {
            if (count != 0) {
                node *temp = new node(data, head->next);
                head->next = temp;
            } else {
                head->next = new node(data);
            }
            count++;
            return true;
        }
        node *pre = head;
        for (int i = 0; i < pos; ++i) {
            pre = pre->next;
        }
        node *temp = new node(data, pre->next);
        pre->next = temp;
        count++;
        return true;
    }

    bool remove(int pos) {
        if (pos < 0 || pos > count - 1) return false;
        if (pos == 0) {
            if (count == 1) {
                delete head->next;
            } else {
                node *temp = head->next;
                head->next = temp->next;
                delete temp;
            }
            count--;
            return true;
        }
        node *pre = head;
        for (int i = 0; i < pos; i++) {
            pre = pre->next;
        }
        node *temp = pre->next;
        pre->next = temp->next;
        delete temp;
        count--;
        return true;
    }

    int size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    T at(int pos) const {
        if (pos < 0 || pos > count - 1) {
            throw 1;
        }
        node *temp = head;
        for (int i = 0; i < pos + 1; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    void clear() {
        int tcount = count;
        for (int i = 0; i < tcount; ++i) {
            remove(0);
        }
    }

    void trave() {
        for (int i = 0; i < count; ++i) {
            std::cout << at(i);
            if (i != count - 1) {
                std::cout << " ";
            }
        }
    }

private:
    struct node {
        T data;
        node *next;

        node(T d, node *n = nullptr) : data(d), next(n) {};
    };

    node *head;
    int count;
};
