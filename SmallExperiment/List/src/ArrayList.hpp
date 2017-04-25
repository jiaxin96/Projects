#include <iostream>
const unsigned int MAX_SIZE = 20;

template<class T>
class ArrayList {
public:
    ArrayList() {
        count = 0;
    }

    ArrayList(ArrayList<T> &ot) {
        for (int i = 0; i < count; i++) {
            ot.storage[i] = storage[i];
        }
        ot.count = count;
    }

    bool remove(int pos) {
        if (pos < 0 || pos > count - 1) return false;
        for (int i = pos + 1; i < count; i++) {
            storage[i - 1] = storage[i];
        }
        count--;
        return true;
    }

    bool empty() const {
        return count == 0;
    }

    bool full() const {
        return count == MAX_SIZE;
    }

    int size() const {
        return count;
    }

    bool insert(int pos, T data) {
        if (count + 1 > MAX_SIZE || pos > count) return false;
        if (count == 0 && pos == 0) {
            count++;
            storage[0] = data;
            return true;
        }
        if (pos == count) {
            storage[count++] = data;
            return true;
        }
        for (int i = count - 1; i >= pos; i--) {
            storage[i + 1] = storage[i];
        }
        storage[pos] = data;
        count++;
        return true;
    }

    T at(int pos) const {
        if (pos < 0 || pos > count - 1) throw 1;
        return storage[pos];
    }

    void clear() {
        count = 0;
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
    T storage[MAX_SIZE];
    int count;
};
