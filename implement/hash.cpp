#include <iostream>
#include <memory>
#include <functional>
#include <string>

using namespace std;

template<class T>
class Hash{
private:
    T *a;
    
public:
    unsigned long size;
    Hash(unsigned long h_size) {
        a = new T[h_size];
        size = h_size;
        for(unsigned long i=0; i < h_size; i++)
            a[i] = "";
    }
    
    unsigned long myHash(const T key) {
        return hash<T>{}(key) % size;
    }
    
    ~Hash() {
        delete []a;
    }
    
    void add(const unsigned long key, const T value) {
        a[key] = value;
    }
    
    bool exists(const unsigned long key) {
        return a[key] != "";
    }
    
    T get(const unsigned long key) {
        return a[key];
    }
    
    void remove(const unsigned long key) {
        if(key<0 || key  >= size)
            throw invalid_argument("Invilid key.");
        a[key] = "";
    }
};

int main() {
    Hash<string> h(30);
    unsigned long key = h.myHash("iVanlIsh");
    h.add(key, "iVanlIsh");
    cout << key << endl;
    cout << h.exists(key) << endl;
    cout << h.get(key) << endl;
    h.remove(key);
    cout << h.exists(key) << endl;
    return 0;
}
