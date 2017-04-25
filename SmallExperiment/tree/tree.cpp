#include <iostream>
#include <stack>
using namespace std;

template <class T> class tree {
private:
    struct node {
        T data;
        node *lChild;
        node *rChild;
        node(T d, node *l = nullptr, node *r = nullptr)
        : data(d), lChild(l), rChild(r) {}
    };
    node *root;

    int count_fun(node * root) {
        if (root->lChild || root->rChild) {
            int lcount = 0;
            if (root->lChild) lcount = count_fun(root->lChild);
            int rcount = 0;
            if (root->rChild) lcount = count_fun(root->rChild);
            return lcount + rcount + 1;
        } else {
            return 1;
        }
    }

    int sum_fun(node * root) {
        if (!root) return 0;
        return sum_fun(root->lChild) + sum_fun(root->rChild) + root->data;
    }
public:
    // 非递归便利
    void noRePreorder() {
        stack<node *> s;
        node * p = root;
        while (p || s.size()) {
            if (p) {
                s.push(p);
                cout << p->data << " ";
                p = p->lChild;
            } else {
                p = s.top();
                s.pop();
                p = p->rChild;
            }
        }
    }
    int getSumOfNode() {
        return sum_fun(root);
    }

    int countNodeNum() {
        int totalNum = 0;
        if (this->root) totalNum = count_fun(this->root);
        return totalNum;
    }
    tree() { root = nullptr; }
    tree(const tree & ot) { copy(root, ot.root); }
    tree & operator=(const tree &ot) {
        copy(root, ot.root);
    }
    tree symmetric() {
        node *ansroot = nullptr;
        invertcopy(root, ansroot);
        tree temp;
        temp.root = ansroot;
        return temp;
    }

    void invertcopy(node *&myroot, node *&otroot) {
        if (myroot == nullptr)
            return;
        otroot = new node(myroot->data);
        if (myroot->rChild) {
            copy(myroot->rChild, otroot->lChild);
        } else if (myroot->lChild) {
            copy(myroot->lChild, otroot->rChild);
        }
    }

    void copy(node *myroot, node *otroot) {
        if (otroot == nullptr)
            return;
        myroot = new node(otroot->data);
        if (otroot->lChild) {
            copy(myroot->lChild, otroot->lChild);
        } else if (otroot->rChild) {
            copy(myroot->rChild, otroot->rChild);
        }
    }
    ~tree() { destroy(root); }

    bool deleteNode(T d) {
        node *aim = find(root,d);
        if (aim->lChild != nullptr)
            return false;
        delete aim;
        return true;
    }
    void show() {
        if (root == nullptr)
            return;
        cout << "The preorder is:";
        preorder(root);
        cout << endl;
        cout << "The inorder is:";
        inorder(root);
        cout << endl;
        cout << "The posorder is:";
        posorder(root);
        cout << endl;
    }
    void preorder(node *r) {
        if (r == nullptr)
            return;
        cout << r->data << " ";
        if (r->lChild != nullptr)
            preorder(r->lChild);
        if (r->rChild != nullptr)
            preorder(r->rChild);
    }
    void inorder(node *r) {
        if (r == nullptr)
            return;
        if (r->lChild != nullptr)
            inorder(r->lChild);
        cout << r->data << " ";
        if (r->rChild != nullptr)
            inorder(r->rChild);
    }
    void posorder(node *r) {
        if (r == nullptr)
            return;
        if (r->lChild != nullptr)
            posorder(r->lChild);
        if (r->rChild != nullptr)
            posorder(r->rChild);
        cout << r->data << " ";
    }
    void destroy(node *tempRoot) {
        if (tempRoot != nullptr) {
            destroy(tempRoot->lChild);
            destroy(tempRoot->rChild);
            delete tempRoot;
        }
    }

    node *getRoot() { return root; }
    void insert(T d, node *parent, char lrt) {
        if (lrt == 'l') {
            if (parent->lChild == nullptr) {
                parent->lChild = new node(d);
            } else {
                parent->lChild->data = d;
            }
        } else if (lrt == 'r') {
            if (parent->rChild == nullptr) {
                parent->rChild = new node(d);
            } else {
                parent->rChild->data = d;
            }
        } else {
            if (root == nullptr) {
                root = new node(d);
            } else {
                root->data = d;
            }
        }
    }
    node *find(node *temp, T d) {
        node * l = nullptr;
        node * r = nullptr;
        if (temp == nullptr) {
            return nullptr;
        }
        if (temp->data == d) {
            return temp;
        }
        if (temp->lChild != nullptr) {
            l = find(temp->lChild, d);
        }
        if (!l && temp->rChild != nullptr) {
            r = find(temp->rChild, d);
        }
        if (l) {
            return l;
        } else if (r) {
            return r;
        }
        return nullptr;
    }
};
