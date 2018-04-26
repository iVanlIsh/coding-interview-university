#include <iostream>
#include <memory>
#include <list>

using namespace std;

template<class T>
class Node{
public:
    Node<T> *prev, *next;
    T val;
    Node(T value, Node<T> *m_prev, Node<T> *m_next) {
        val = value;
        prev = m_prev;
        next = m_next;
    }
};

template<class T, class Allocator = allocator<T>>
class List{
public:
    Node<T> *first, *last;
    unsigned long s;

public:
    List() {
        first = NULL;
        last = NULL;
        s = 0;
    }

    unsigned long size() {
        return s;
    }

    bool empty() {
        return s==0;
    }

    T value_at(unsigned long index) {
        if(index < 0 or index >= s) return NULL;
        Node<T> *node = first;
        for(unsigned long i = 0; i < index; i++) {
            node = node->next;
        }
        return node->val;
    }

    void push_front(T value) {
        s++;
        Node<T> *node = new Node<T>(value, nullptr, first);
        if(first) first->prev = node;
        first = node;
        if(s==1) last = node;
    }

    unsigned long pop_front() {
        if(s==0)
            throw invalid_argument("Empty list.");
        s--;
        Node<T> *node = first;
        first = first->next;
        if(first) first->prev = NULL;
        if(s==0) last = NULL;
        return node->val;
    }

    void push_back(T value) {
        s++;
        Node<T> *node = new Node<T>(value, last, nullptr);
        if(last) last->next = node;
        last = node;
        if(s==1) first = node;
    }

    unsigned long pop_back() {
        if(s==0)
            throw invalid_argument("Empty list.");
        s--;
        Node<T> *node = last;
        last = last->prev;
        if(last) last->next = NULL;
        if(s==0) first = NULL;
        return node->val;
    }

    T front() {
        return first? first->val : NULL;
    }

    T back() {
        return last? last->val : NULL;
    }

    void insert(unsigned long index, T value) {
        if(index < 0 || index > s)
            throw invalid_argument("Invalid index.");
        if(index==0) {
            Node<T> *new_node = new Node<T>(value, NULL, first);
            if(first) first->prev = new_node;
            first = new_node;
            if(s==0) last = new_node;
        } else if (index==s) {
            Node<T> *new_node = new Node<T>(value, last, NULL);
            if(last) last->next = new_node;
            last = new_node;
        } else {
            Node<T> *node = first;
            for (unsigned long i = 0; i < index; i++)
                node = node->next;
            Node<T> *new_node = new Node<T>(value, node, node->next);
            node->prev->next = new_node;
            node->next = new_node;
        }
        s++;
    }

    void erase(unsigned long index) {
        if(index < 0 || index >= s)
            throw invalid_argument("Invalid index.");
        s--;
        Node<T> *node = first;
        for(unsigned long i = 0; i < index; i++) {
            node = node->next;
        }
        if(!node->prev) {
            first = node->next;
        } else {
            node->prev->next = node->next;
        }
        if(!node->next) {
            last = node->prev;
        } else {
            node->next->prev = node->prev;
        }
        delete node;
    }

    //TODO
    T value_n_from_end(unsigned long index) {} // same as value_at()

    void reverse() {
        Node<T> *node = first;
        first = last;
        last = node;
        while(node) {
            Node<T> *o_next = node->next;
            node->next = node->prev;
            node->prev = o_next;
            node = o_next;
        }
    }

    void remove_value(T value) {
        Node<T> *node = first;
        while(node) {
            if(node->val==value) {
                if(node->prev)
                    node->prev->next = node->next;
                else
                    first = node->next;
                if(node->next)
                    node->next->prev = node->prev;
                else
                    last = node->prev;
                delete node;
                s--;
                break;
            }
            node = node->next;
        }
    }

    //TODO
//    ~List() {}
//    T operator=() {}
//    T assign() {}
//
//    T front() {}
//    T back() {}
//
//    iterator begin() {}
//    iterator cbegin() {}
//    iterator end() {}
//    iterator cend() {}
//    iterator rbegin() {}
//    iterator crbegin() {}
//
//    unsigned long max_size() {}
//
//    void clear() {}
//    void insert() {}
//    void emplace() {}
//    void erase() {}
};

int main() {
    List<int> v_test;
    v_test.push_front(1);
    v_test.push_front(2);
    v_test.push_front(4);
    v_test.push_front(3);
    cout << "Size: " << v_test.size() << endl;
    v_test.pop_front();
    v_test.insert(0,1);
    cout << "First value: " << v_test.value_at(0) << endl;
    v_test.push_front(233);
    v_test.push_back(122);
    cout << "Last value: " << v_test.back() << endl;
    cout << "First value: " << v_test.front() << endl;
    cout << "Last value: " << v_test.pop_back() << endl;
    cout << "First value: " << v_test.pop_front() << endl;
    cout << "Size: " << v_test.size() << endl;
    v_test.erase(1);
    cout << "Size: " << v_test.size() << endl;
    v_test.reverse();
    v_test.push_back(122);
    v_test.push_front(233);
    v_test.remove_value(233);
    cout << "Is empty: " << v_test.empty() << endl;

    Node<int> *node = v_test.first;
    while(node) {
        cout << node->val << " ";
        node = node->next;
    }
    cout<< endl;

    node = v_test.last;
    while(node) {
        cout << node->val << " ";
        node = node->prev;
    }
    cout<<endl;
    return 0;
}