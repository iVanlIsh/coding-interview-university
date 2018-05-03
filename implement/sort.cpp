#include <iostream>
#include <climits>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

void print(vector<int> v) {
	for(int i=0; i<v.size(); i++)
		cout<< v[i] << " ";
	cout << endl;
}

void swap(vector<int> *v, int i, int j) {
	if(i==j) return;
	v->at(i) ^= v->at(j);
	v->at(j) ^= v->at(i);
	v->at(i) ^= v->at(j);
}

//TODO: Intro sort
void quick_sort_r(vector<int> *v, int l, int r) {
	int i=l+1, j=r;
	while(i<j) {
		while(v->at(l)<=v->at(j)&&i<j) j--;
		while(v->at(i)<=v->at(l)&&i<j) i++;
		swap(v, i, j);
	}
	if(v->at(i)<=v->at(l)) {
		swap(v, i, l);
	} else {
		swap(v, --i, l);
	}
	if(l<i-1)
		quick_sort_r(v, l, i-1);
	if(i+1<r)
		quick_sort_r(v, i+1, r);
}

vector<int> quick_sort(vector<int> v) {
	quick_sort_r(&v, 0, v.size()-1);
	return v;
}

//TODO: Merge sort is more sutible with linked list.
vector<int> merge_sort(vector<int> v) {
	return v;
}

vector<int> bubble_sort(vector<int> v) {
	for(int i=0; i<v.size()-1; i++)
		for(int j=0; j<v.size()-1-i; j++)
			if(v[j]>v[j+1])
				swap(&v, j, j+1);
	return v;
}

vector<int> insert_sort(vector<int> v) {
	if(v.size()<=1) return v;
	for(int i=1; i<v.size(); i++) {
		int tmp = v[i],j=i-1;
		for(; j>=0 && v[j]>tmp; j--)
			v[j+1] = v[j];
		v[j+1] = tmp;
	}
	return v;
}

//TODO: Smooth sort
void heap_sort_up(vector<int> *v, int j){
	while((j-1)/2>=0){
		if(v->at(j)>v->at((j-1)/2)) {
			swap(v, j, (j-1)/2);
			j = (j-1)/2;
		} else {
			break;
		}
	}
}

void heap_sort_down(vector<int> *v, int j, int size){
	while(((j+1)<<1)-1<size) {
		if(v->at(j)<v->at(((j+1)<<1)-1) && \
			((j+1)<<1 >= size || v->at((j+1)<<1)<=v->at(((j+1)<<1)-1))) {
			swap(v, j, ((j+1)<<1)-1);
			j = ((j+1)<<1)-1;
		} else if((j+1)<<1 < size && v->at(j)<v->at((j+1)<<1)) {
			swap(v, j, (j+1)<<1);
			j = (j+1)<<1;
		} else {
			break;
		}
	}
}

vector<int> heap_sort(vector<int> v) {
	if(v.size()<=1) return v;
	for(int i=1; i<v.size(); i++){
		heap_sort_up(&v, i);
	}
	for(int i=v.size()-1; i>0; i--) {
		swap(&v, 0, i);
		heap_sort_down(&v, 0, i);
	}
	return v;
}

vector<int> selection_sort(vector<int> v) {
	for(int i=0; i<v.size()-1; i++) {
		int min=i;
		for(int j=i+1; j<v.size(); j++)
			if(v[min]>v[j]) min = j;
		swap(&v, i, min);
	}
	return v;
}

//TODO: insert sort + merge sort
vector<int> tim_sort(vector<int> v) {
	return v;
}

vector<int> shell_sort(vector<int> v) {
	int h = 1;
	while(h<v.size()/3) h = h*3+1;
	while(h>=1) {
		for(int i=h; i<v.size(); i++)
			for(int j=i; j>=h && v[j]<v[j-h]; j-=h)
				swap(&v, j, j-h);
		h/=3;
	}
	return v;
}

int main() {
	int a = 1;
	vector<int> v(1000);
	for(int i=0; i<1000; i++)
		v[i] = rand();
	// print(v);
	clock_t start;
	start = clock();
	bubble_sort(v);
	cout<< "Bubble sort: " << difftime(clock(), start) << "ms" << endl;
	start = clock();
	insert_sort(v);
	cout<< "Insert sort: " << difftime(clock(), start) << "ms" << endl;
	start = clock();
	shell_sort(v);
	cout<< "Shell sort: " << difftime(clock(), start) << "ms" << endl;
	// start = clock();
	// print(tim_sort(v));
	// cout<< "Tim sort: " << difftime(clock(), start) << "ms" << endl;
	// start = clock();
	// print(merge_sort(v));
	// cout<< "Merge sort: " << difftime(clock(), start) << "ms" << endl;
	start = clock();
	selection_sort(v);
	cout<< "Selection sort: " << difftime(clock(), start) << "ms" << endl;
	start = clock();
	heap_sort(v);
	cout<< "Heap sort: " << difftime(clock(), start) << "ms" << endl;
	start = clock();
	quick_sort(v);
	cout<< "Quick sort: " << difftime(clock(), start) << "ms" << endl;
	return 0;
}
