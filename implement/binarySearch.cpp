#include <iostream>
using namespace std;
template<typename T>
unsigned long bsearch(T target, unsigned long start, unsigned long end, T* arr) {
	if (arr[start] == target) return start;
	if (start+1 >= end) return -1;
	unsigned long mid = (start + end) / 2;
	if (arr[mid] > target) return bsearch(target, start, mid, arr);
	if (arr[mid] <= target) return bsearch(target, mid, end, arr);
}

int main() {
	unsigned long size;
	cin >> size;
	int *arr = new int[size];
	for(int i=0; i < size; i++)
		cin >> arr[i];
	int target;
	cin >> target;
	cout << bsearch(target, 0, size, arr) << endl;
}