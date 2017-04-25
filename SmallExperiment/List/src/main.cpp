#include <iostream>
#include "ArrayList.hpp"
#include "ListedList.hpp"

using namespace std;

template<class T>
bool Ado(ArrayList<T> & alist) {
    cout << "Please inpput your operation!\n";
    cout << "1.insert 2.remove 3.clear 4.show 5.size 6.empty 7.full 8.exit\n";
    int op;
    cin >> op;
    int pos;
    T data;
    switch (op) {
        case 1:
            cout << "input data and postion you want to insert:";
            cin >> data >> pos;
            if (alist.insert(pos, data)) {
                cout << "insert successfully!\n";
            } else {
                cout << "insert failed!\n";
            }
            return true;
        case 2:
            cout << "input where you want to remove:";
            cin >> pos;
            if (alist.remove(pos)) {
                cout << "remove successfully!\n";
            } else {
                cout << "remove failed\n";
            }
            return true;
        case 3:
            alist.clear();
            cout << "clear successfully!\n";
            return true;
        case 4:
            try {
                cout << "The data is:";
                alist.trave();
                cout << endl;
            }
            catch (int) {
                cout << "getElement failed\n";
            }
            return true;
        case 5:
            cout << "The lise size is :" << alist.size() << endl;
            return true;
        case 6:
            if (alist.empty()) cout << "List is empty.\n";
            else cout << "List is not empty.\n";
            return true;
        case 7:
            if (alist.full()) cout << "List is full.\n";
            else cout << "List is not full.\n";
            return true;
        case 8:
            return false;
        default:
            return true;
    }
    return true;
}

template<class T>
bool Ldo(ListedList<T> & llist) {
    cout << "Please inpput your operation!\n";
    cout << "1.insert 2.remove 3.clear 4.show 5.size 6.empty 7.exit\n";
    int op;
    cin >> op;
    int pos;
    T data;
    switch (op) {
        case 1:
            cout << "input data and postion you want to insert:";
            cin >> data >> pos;
            if (llist.insert(pos, data)) {
                cout << "insert successfully!\n";
            } else {
                cout << "insert failed!\n";
            }
            return true;
        case 2:
            cout << "input where you want to remove:";
            cin >> pos;
            if (llist.remove(pos)) {
                cout << "remove successfully!\n";
            } else {
                cout << "remove failed\n";
            }
            return true;
        case 3:
            llist.clear();
            cout << "clear successfully!\n";
            return true;
        case 4:
            try {
                cout << "The data is:";
                llist.trave();
                cout << endl;
            }
            catch (int) {
                cout << "getElement failed\n";
            }
            return true;
        case 5:
            cout << "The lise size is :" << llist.size() << endl;
            return true;
        case 6:
            if (llist.empty()) cout << "List is empty.\n";
            else cout << "List is not empty.\n";
            return true;
        case 7:
            return false;
        default:
            return true;
    }
    return true;
}

template<class T>
void test() {
    // test ArrayList
    {
        cout << "ArrayList test\n";
        ArrayList<T> alist;
        while (Ado<T>(alist)) {}
    }
    cout << "-----------------------------------\n";
    {
        cout << "ListedList test\n";
        ListedList<T> llist;
        while (Ldo<T>(llist)) {}
    }
}

int main(int argc, char const *argv[]) {
    test<char>();
    return 0;
}
