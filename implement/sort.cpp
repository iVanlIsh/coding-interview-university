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

//TODO: Optimization
vector<int> quick_sort(vector<int> v, int l=0, int r=INT_MAX) {
	if(r==INT_MAX) r = v.size()-1;
	int i=l, j=r;
	while(i!=j) {
		while(v[i]<=v[j]&&i!=j) j--;
		if(i!=j) {
			v[i]^=v[j];
			v[j]^=v[i];
			v[i]^=v[j];
		}
		while(v[i]<=v[j]&&i!=j) i++;
		if(i!=j) {
			v[i]^=v[j];
			v[j]^=v[i];
			v[i]^=v[j];
		}
	}
	if(l<i-1)
		v = quick_sort(v, l, i-1);
	if(i+1<r)
		v = quick_sort(v, i+1, r);
	return v;
}

vector<int> merge_sort(vector<int> v) {

	return v;
}

vector<int> bubble_sort(vector<int> v) {
	for(int i=0; i<v.size()-1; i++)
		for(int j=i+1; j<v.size(); j++)
			if(v[i]>v[j]) {
				v[i] ^= v[j];
				v[j] ^= v[i];
				v[i] ^= v[j];
			}
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

vector<int> heap_sort_r(vector<int> v, int j){
		while(j>0){
			if(v[j]>v[(j-1)/2]){
				v[j] ^= v[(j-1)/2];
				v[(j-1)/2] ^= v[j];
				v[j] ^= v[(j-1)/2];
				j = (j-1)/2;
			} else {
				break;
			}
		}

}
vector<int> heap_sort(vector<int> v) {
	if(v.size()<=1) return v;
	for(int i=1; i<v.size(); i++){
		v = heap_sort_r(v, i);
	}

	return v;
}

vector<int> selection_sort(vector<int> v) {
	return v;
}

vector<int> tim_sort(vector<int> v) {
	return v;
}

vector<int> shell_sort(vector<int> v) {
	return v;
}

int main() {
	vector<int> v(25);
	for(int i=0; i<25; i++)
		v[i] = rand()%200;
	print(v);
	time_t start = time(nullptr);
	print(quick_sort(v));
	cout<< "Quick sort: " << difftime(time(nullptr), start) * 1000 << "ms" << endl;
	start = time(nullptr);
	print(merge_sort(v));
	cout<< "Merge sort: " << difftime(time(nullptr), start) * 1000 << "ms" << endl;
	start = time(nullptr);
	print(bubble_sort(v));
	cout<< "Bubble sort: " << difftime(time(nullptr), start) * 1000 << "ms" << endl;
	start = time(nullptr);
	print(insert_sort(v));
	cout<< "Insert sort: " << difftime(time(nullptr), start) * 1000 << "ms" << endl;
	start = time(nullptr);
	print(heap_sort(v));
	cout<< "Heap sort: " << difftime(time(nullptr), start) * 1000 << "ms" << endl;
	start = time(nullptr);
	print(selection_sort(v));
	cout<< "Selection sort: " << difftime(time(nullptr), start) * 1000 << "ms" << endl;
	start = time(nullptr);
	print(tim_sort(v));
	cout<< "Tim sort: " << difftime(time(nullptr), start) * 1000 << "ms" << endl;
	start = time(nullptr);
	print(shell_sort(v));
	cout<< "Shell sort: " << difftime(time(nullptr), start) * 1000 << "ms" << endl;
	return 0;
}
