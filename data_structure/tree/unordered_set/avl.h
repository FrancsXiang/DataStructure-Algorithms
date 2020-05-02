#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef unsigned long long ULL;

template<typename T>
struct node {
	T data;
	string val;
	struct node<T>* l, * r;
	node<T>(T _data, string _val) : l(NULL), r(NULL), data(_data), val(_val) {};
};

template<typename T>
class AVL
{
public:
	AVL();
	~AVL();
	ULL len;
	void insert(T data, string);// data < node.data (left branch of node)
	void erase(T data);
	bool search(T data);
	void debug();
	void release();
	vector<T> sort();
	string first_elem();
	string last_elem();
private:
	node<T>* p, * head;
	vector<T> con;
	int height(node<T>* root);
	void release_space(node<T>* root);
	void in_order(node<T>* root);
	node<T>* l_rotate(node<T>* root);
	node<T>* r_rotate(node<T>* root);
	node<T>* lr_rotate(node<T>* root);
	node<T>* rl_rotate(node<T>* root);
	node<T>* _insert(node<T>* root, T data, string);
	node<T>* _erase(node<T>* root, T data);
	bool _search(node<T>* root, T data);
	int balance(node<T>* root);
	T findMin(node<T>* root);
	bool valid(node<T>* root);
	void _debug(node<T>* root);
	string _first_elem(node<T>* root);
	string _last_elem(node<T>* root);
};

template<typename T>
AVL<T>::AVL()
{
	len = 0;
	head = NULL;
}

template<typename T>
AVL<T>::~AVL()
{
	con.clear();
	release_space(head);
}

template<typename T>
int AVL<T>::height(node<T>* root) {
	if (!root) return 0;
	else return max(height(root->l), height(root->r)) + 1;
}

template<typename T>
void AVL<T>::release_space(node<T>* root) {
	if (root) {
		release_space(root->l); release_space(root->r);
		delete root;
	}
}

template<typename T>
void AVL<T>::release() {
	len = 0;
	con.clear();
	release_space(head);
	head = NULL;
}

template<typename T>
node<T>* AVL<T>::l_rotate(node<T>* root) {
	node<T>* p = root->r;
	root->r = p->l;
	p->l = root;
	return p;
}

template<typename T>
node<T>* AVL<T>::r_rotate(node<T>* root) {
	node<T>* p = root->l;
	root->l = p->r;
	p->r = root;
	return p;
}

template<typename T>
node<T>* AVL<T>::lr_rotate(node<T>* root) {
	root->l = l_rotate(root->l);
	return r_rotate(root);
}

template<typename T>
node<T>* AVL<T>::rl_rotate(node<T>* root) {
	root->r = r_rotate(root->r);
	return l_rotate(root);
}

template<typename T>
node<T>* AVL<T>::_insert(node<T>* root, T data, string s) {
	if (!root) {
		p = new node<T>(data, s);//avoid wild_pointer_explosion
		return p;
	}
	else {
		if (data < root->data) {
			root->l = _insert(root->l, data, s);
			if (height(root->l) - height(root->r) == 2) return data < root->l->data ? r_rotate(root) : lr_rotate(root);
		}
		else {
			root->r = _insert(root->r, data, s);
			if (height(root->r) - height(root->l) == 2) return data >= root->r->data ? l_rotate(root) : rl_rotate(root);
		}
		return root;
	}
}

template<typename T>
void AVL<T>::insert(T data, string s) {
	if (!search(data)) head = _insert(head, data, s), len++;
	if (!valid(head)) cout << "not balanced" << endl;
}

template<typename T>
node<T>* AVL<T>::_erase(node<T>* root, T data) {
	if (!root) return NULL;
	if (data < root->data) root->l = _erase(root->l, data);
	else if (data > root->data) root->r = _erase(root->r, data);
	else {
		if (root->l && root->r) {
			root->data = findMin(root->r);
			root->r = _erase(root->r, root->data);
		}
		else
			return  root->l ? root->l : root->r;
	}
	if (balance(root) < -1) {
		if (balance(root->r) <= 0) return l_rotate(root);
		else return rl_rotate(root);
	}
	if (balance(root) > 1) {
		if (balance(root->l) >= 0) return r_rotate(root);
		else return lr_rotate(root);
	}
	return root;
}

template<typename T>
T AVL<T>::findMin(node<T>* root) {
	while (root->l) root = root->l;
	return root->data;
}

template<typename T>
int AVL<T>::balance(node<T>* root) {
	return root ? (height(root->l) - height(root->r)) : 0;
}


template<typename T>
void AVL<T>::erase(T data) {
	if (!search(data)) head = _erase(head, data), len--;
	if (!valid(head)) cout << "not balanced" << endl;
}

template<typename T>
vector<T> AVL<T>::sort() {
	con.clear();
	in_order(head);
	return con;
}

template<typename T>
void AVL<T>::in_order(node<T>* root) {
	if (root) {
		in_order(root->l);
		con.push_back(root->data);
		in_order(root->r);
	}
}

template<typename T>
bool AVL<T>::_search(node<T>* root, T data) {
	if (!root) return false;
	else if (data < root->data) return _search(root->l, data);
	else if (data > root->data) return _search(root->r, data);
	else return true;
}

template<typename T>
bool AVL<T>::search(T data) {
	return _search(head, data);
}

template<typename T>
bool AVL<T>::valid(node<T>* root) {
	if (root) {
		if (abs(height(root->l) - height(root->r)) <= 1) return valid(root->l) && valid(root->r);
		else return false;
	}
	else
		return true;
}

template<typename T>
void AVL<T>::_debug(node<T>* root) {
	if (root) {
		if (root->l) cout << (root->data) << "->" << root->l->data << endl;
		if (root->r) cout << (root->data) << "->" << root->r->data << endl;
		_debug(root->l); _debug(root->r);
	}
}

template<typename T>
void AVL<T>::debug() {
	_debug(head);
}

template<typename T>
string AVL<T>::_first_elem(node<T>* root) {
	if (len == 0) throw "no elem error!";
	return root->val;
}

template<typename T>
string AVL<T>::first_elem() {
	return _first_elem(head);
}

template<typename T>
string AVL<T>::_last_elem(node<T>* root) {
	if (len == 0) throw "no elem error!";
	while (root->r) root = root->r;
	return root->val;
}

template<typename T>
string AVL<T>::last_elem() {
	return _last_elem(head);
}
