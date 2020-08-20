//segment_tree implementation sample with section_sum by array.
#include <iostream>
#include <string>
#define MAXN 9999999
using namespace std;

double segTree[MAXN];

double init(double* arr, int start, int end, int index) {
	if (start == end) return segTree[index] = arr[start];
	else {
		int mid = (start + end) / 2;
		return segTree[index] = init(arr, start, mid, 2 * index + 1) + init(arr, mid + 1, end, 2 * index + 2);
	}
}

double update(double* arr, int start, int end, int arr_idx, int tree_idx, double new_val) {
	if (start == end) return segTree[tree_idx] = new_val;
	else {
		int mid = (start + end) / 2;
		if(mid >= arr_idx) return segTree[tree_idx] = update(arr, start, mid - 1, arr_idx, 2 * tree_idx + 1, new_val) + segTree[2 * tree_idx + 2];
		else return segTree[tree_idx] = update(arr, mid + 1, end, arr_idx, 2 * tree_idx + 2, new_val) + segTree[2 * tree_idx + 1];
	}
}

double section_query(double* arr, int start, int end,int search_start,int search_end,int tree_idx) {
	int mid = (start + end) / 2;
	if (start == search_start && end == search_end) return segTree[tree_idx];
	if (mid < search_start) return section_query(arr, mid + 1, end, search_start, search_end, 2 * tree_idx + 2);
	else if (mid + 1 > search_end) return section_query(arr, start, mid, search_start, search_end, 2 * tree_idx + 1);
	else return section_query(arr, start, mid, search_start, mid, 2 * tree_idx + 1) + section_query(arr, mid + 1, end, mid + 1, search_end, 2 * tree_idx + 2);
}

int main()
{
	double arr[5] = { 0,1,2,3,4 };
	init(arr, 0, 4, 0);
	update(arr, 0, 4, 2, 0, 3);
	for (int i = 0; i < 10; i++) cout << segTree[i] << " ";
	cout << endl;
	cout << section_query(arr, 0, 4, 2, 4, 0) << endl;
	return 0;
}
