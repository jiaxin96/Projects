#include "tree.cpp"
#include <cstdio>
using namespace std;
template <class T> bool doSth(tree<T> &t) {
    int op = 0;
    cout << "1.insert 2.show 3.Get Symmetic Tree 4.Delete node 5.exit 6.countNodeNum 7.getSumOfNode 8.noRePreorder\n";
    cout << "please input your operation number:";
    cin >> op;
    switch (op) {
        case 1:
            cout << "input your data and it's root data and "
                    "what type it is[(leftChild(l)) rightChild(r) root(t)]"
                 << endl;
            T d, p;
            char lrt;
            cin >> d >> p >> lrt;
            if (lrt == 't') {
                if (t.getRoot() != nullptr) {
                    if (t.find(t.getRoot(), d) != nullptr) {
                        cout << "Insert faild! Data has existed\n";
                    }
                    else {
                        t.insert(d, t.find(t.getRoot(), p), lrt);
                        cout << "insert successfuly\n";
                    }
                }
                else {
                    t.insert(d, t.getRoot(), lrt);
                    cout << "insert successfuly\n";
                }

            }
            else if (t.find(t.getRoot(), d) != nullptr) {
                cout << "Insert faild! Data has existed\n";
            }
            else if (!t.find(t.getRoot(), p)) {
                cout << "Insert faild! The parent isn't exist\n";
            }
            else {
                t.insert(d, t.find(t.getRoot(), p), lrt);
                cout << "insert successfuly\n";
            }
            return true;
        case 2:
            cout << "the tree is:\n";
            t.show();
            return true;
        case 3: {
            tree<T> temp = t.symmetric();
            cout << "The symmetric tree is:\n";
            temp.show();
            return true;
        }
        case 4:
            T td;
            cout << "Delete the data you want to delete:";
            cin >> td;
            if (t.find(t.getRoot(), td) == nullptr) {
                cout << "No this data\n";
            }
            else if ((t.find(t.getRoot(), td))->lChild != nullptr) {
                cout << "This is not a leaf!You can't delete it!\n";
            }
            else {
                t.deleteNode(td);
                cout << "Delete successfuly\n";
            }
            return true;
        case 5:
            cout << "Test Over!";
            return false;
        case 6:
            cout << "The number of node is : " << t.countNodeNum() << endl;
            return true;
        case 7:
            cout << "the totalNum'Sum is : " << t.getSumOfNode() << endl;
            return true;
        case 8:
            cout << "noRePreorder:\n";
            t.noRePreorder();
            cout << endl;

        default:break;
    }
    return true;
}

void test() {
    freopen("data", "r", stdin);
    cout << "Binary Tree test!" << endl;
    tree<int> t1;
    while (doSth<int>(t1));
}

int main() { test(); }
