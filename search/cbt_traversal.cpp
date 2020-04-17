/*
This file shows three classic traversal forms of complete binary tree which implemented by array with stack.
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> pre_order(vector<int>& tree) {
	vector<int> res;
	stack<int> st;
	st.push(0);
	while (!st.empty()) {
		auto item = st.top();
		st.pop();
		res.push_back(tree[item]);
		if (2 * item + 2 < tree.size()) st.push(2 * item + 2);
		if (2 * item + 1 < tree.size()) st.push(2 * item + 1);
	}
	return res;
}

vector<int> in_order(vector<int>& tree) {
	stack<int> st;
	vector<int> res;
	vector<bool> l(tree.size(), false);
	st.push(0);
	while (!st.empty()) {
		auto item = st.top();
		st.pop();
		if (2 * item + 1 < tree.size() && !l[item]) {
			while (item < tree.size()) {
				st.push(item);
				l[item] = true;
				item = 2 * item + 1;
			}
		}
		else {
			res.push_back(tree[item]);
			if (2 * item + 2 < tree.size()) st.push(2 * item + 2);
		}
	}
	return res;
}

vector<int> post_order(vector<int>& tree) {
	stack<int> st;
	vector<int> res;
	vector<bool> l(tree.size(), false), r(tree.size(), false);
	st.push(0);
	while (!st.empty()) {
		auto item = st.top();
		st.pop();
		if (2 * item + 1 < tree.size() && !l[item]) {
			while (item < tree.size()) {
				st.push(item);
				l[item] = true;
				item = 2 * item + 1;
			}
		}
		else {
			if (2 * item + 2 < tree.size() && !r[item]) {
				st.push(item);
				st.push(2 * item + 2);
				r[item] = true;
			}else 
				res.push_back(tree[item]);
		}
	}
	return res;
}

int main()
{
	vector<int> tree(3);
	for (int i = 0; i < tree.size(); i++) tree[i] = i + 1;
	auto res = post_order(tree);
	for (int i = 0; i < res.size(); i++) cout << res[i] << " ";
	return 0;
}
