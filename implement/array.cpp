#include <iostream>
#include <memory>

using namespace std;

template<class T>
class Vector{
private:
    allocator<T> a1;
    T *a;

protected:
    void resize(const unsigned long new_capacity) {
        T *b = a1.allocate(new_capacity);
        copy(a, a+capacity, b);

        a1.destroy(a);
        a1.deallocate(a, capacity);

        a = b;
        capacity = new_capacity;
    }

public:
    unsigned long size, capacity;
    Vector() {
        a = a1.allocate(16);
        capacity = 16;
        size = 0;
    }

    //TODO
    //void* operator new(size_t size) {}
    //void operator delete(void* d) {}
    //void swap(Vector<T> &v) {}
		//void shrink_to_fit() {}

    ~Vector() {
        a1.destroy(a);
        a1.deallocate(a, capacity);
    }

    bool is_empty() {
        return size==0;
    }

    T at(const int index) {
        return a[index];
    }

    void push(const T item) {
        if(size >= capacity) resize(capacity*2);
        a[size] = item;
        size++;
    }

    void insert(const int index, const T item) {
        if(index < 0 || index >= size)
            throw invalid_argument("Invalid index.");
        if(size >= capacity) resize(capacity*2);
        for(unsigned long i = size - 1; i>index; i--) {
            a[i] = a[i-1];
        }
        a[index] = item;
        size++;
    }

    void prepend(const T item) {
        if(size >= capacity) resize(capacity*2);
        if(size==0) {
            a[0] = item;
            size++;
        }
        for(unsigned long i = size - 1; i>0; i--) {
            a[i] = a[i-1];
        }
        a[0] = item;
        size++;
    }

    T pop() {
        if(size==0) return -1;
        size--;
        if(size<capacity/2) resize(capacity/2);
        return a[size];
    }

    void remove(const T item) {
        int j=0;
        for(unsigned long i=0; i<size-j; i++) {
            if(a[i+j]==item) j++;
            if(i+j==size) break;
            a[i] = a[i+j];
        }
        size -= j;
        if(size<capacity/2 && capacity > 8) resize(capacity/2);
    }

    long long find(const T item) {
        for(unsigned long i=0; i<size; i++) {
            if(a[i]==item) return i;
        }
        return -1;
    }

    void erase(const unsigned long index) {
        for(unsigned long i=index; i<size-1; i++) {
            a[i] = a[i+1];
        }
        size--;
    }

    T operator[] (const int index) {
        if(index < 0 || index >= size) throw invalid_argument("Invalid index.");
        return a[index];
    }

    friend ostream& operator<<(ostream& os, Vector<T> &vec) {
        for(int i=0; i<vec.size-1; i++) os << vec.at(i) << " ";
        return os << vec[vec.size-1] << endl;
    }
};

int main() {
    Vector<int> v_test;
    v_test.push(1);
    cout << "Position 0: " << v_test.at(0) << endl;
    cout << "Position 0: " << v_test[0] << endl;
    v_test.pop();
    cout << "Size: " << v_test.size << " Capacity: " << v_test.capacity << endl;
    v_test.prepend(10);
    v_test.insert(0,-1);
    v_test.prepend(10);
    v_test.push(10);
    v_test.remove(10);
    v_test.push(100);
    cout << v_test;
    cout << "Index of 0: " << v_test.find(0) << endl;
    cout << "Is empty: " << v_test.is_empty() << endl;
    return 0;
}
