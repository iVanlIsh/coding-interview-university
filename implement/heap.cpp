#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
class Heap:public vector<T> {
public:
    Heap() {}
    void sift_down(long int i, long int size) {
        if(size<=1) return;
        long int l=(i+1)*2-1;
        long int r=l+1;
        if((*this)[l]>=(*this)[i] && (r>=size || (*this)[l]>=(*this)[r])){
            (*this)[i] ^= (*this)[l];
            (*this)[l] ^= (*this)[i];
            (*this)[i] ^= (*this)[l];
            if((l+1)*2-1 < size)
                sift_down(l,size);
        } else if(r<size && (*this)[r]>(*this)[i] && (*this)[r]>(*this)[l]) {
            (*this)[i] ^= (*this)[r];
            (*this)[r] ^= (*this)[i];
            (*this)[i] ^= (*this)[r];
            if((r+1)*2-1 < size)
                sift_down(r,size);
        }
    }

    void heapify() {
        for(long int i=this->size()/2-1; i>=0; i--) {
            sift_down(i,this->size());
        }
    }
    void sift_up(T value) {
        if(this->size()<=1) return;
        long int i = this->size()-1;
        while(i>0 && (*this)[i]>(*this)[(i-1)/2]) {
            (*this)[i] ^= (*this)[(i-1)/2];
            (*this)[(i-1)/2] ^= (*this)[i];
            (*this)[i] ^= (*this)[(i-1)/2];
            i = (i-1)/2;
        }
    }

    void insert(T value) {
        this->push_back(value);
        sift_up(value);
    }

    T get_max() {
        return (*this)[0];
    }

    long int get_size() {
        return this->size();
    }

    bool is_empty() {
        return this->empty();
    }

    T extract_max() {
        T temp = (*this)[0];
        (*this)[0] = (*this)[this->size()-1];
        this->pop_back();
        sift_down(0,this->size());
        return temp;
    }

    void remove(long int i) {
        if(i<0 || i>=this->size())
            throw invalid_argument("Invilid size.");
        (*this)[i] = (*this)[this->size()-1];
        this->pop_back();
        sift_down(i,this->size());
    }

    void heap_sort() {
        long int size = this->size();
        while(size) {
            (*this)[0] ^= (*this)[size-1];
            (*this)[size-1] ^= (*this)[0];
            (*this)[0] ^= (*this)[size-1];
            size--;
            sift_down(0,size);
        }
    }
};

int main() {
    Heap<int> h;
    h.push_back(8);
    h.push_back(3);
    h.push_back(4);
    h.push_back(3);
    h.push_back(2);
    h.heapify();
    h.insert(7);
    h.insert(3);
    for(long int i=0; i<h.size(); i++) {
        cout << h[i] << " ";
    }
    h.remove(2);
    cout << h.get_max() << h.get_size() << endl;
    cout << h.is_empty() << endl;
    cout << h.extract_max() << endl;
    h.heap_sort();
    for(long int i=0; i<h.size(); i++) {
        cout << h[i] << " ";
    }
    cout << endl;
    return 0;
}
