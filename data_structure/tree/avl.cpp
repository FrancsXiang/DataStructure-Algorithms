/*
	This file implements the data_structure of avl tree.(release_version)
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

template<typename T>
struct node {
	T data;
	struct node<T>* l, * r;
	node<T>(T _data) : l(NULL), r(NULL), data(_data) {};
};

template<typename T>
class AVL
{
public:
	AVL();
	~AVL();
	void insert(T data);// data < node.data (left branch of node)
	void erase(T data);
	vector<T> sort();
	bool search(T data);
	void debug();
private:
	node<T>* head;
	vector<T> con;
	int height(node<T>* root);
	void release_space(node<T>* root);
	void in_order(node<T>* root);
	node<T>* l_rotate(node<T>* root);
	node<T>* r_rotate(node<T>* root);
	node<T>* lr_rotate(node<T>* root);
	node<T>* rl_rotate(node<T>* root);
	node<T>* _insert(node<T>* root, T data);
	node<T>* _erase(node<T>* root, T data);
	bool _search(node<T>* root, T data);
	int balance(node<T>* root);
	T findMin(node<T>* root);
	bool valid(node<T>* root);
	void _debug(node<T>* root);
};

template<typename T>
AVL<T>::AVL()
{
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
node<T>* AVL<T>::_insert(node<T>* root, T data) {
	if (!root) {
		node<T>* p = new node<T>(data);
		return p;
	}
	else {
		if (data < root->data) {
			root->l = _insert(root->l, data);
			if (height(root->l) - height(root->r) == 2) return data < root->l->data ? r_rotate(root) : lr_rotate(root);
		}
		else {
			root->r = _insert(root->r, data);
			if (height(root->r) - height(root->l) == 2) return data >= root->r->data ? l_rotate(root) : rl_rotate(root);
		}
		return root;
	}
}

template<typename T>
void AVL<T>::insert(T data) {
	if (!search(data)) head = _insert(head,data);
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
		}else 
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
	return root?(height(root->l) - height(root->r)):0;
}


template<typename T>
void AVL<T>::erase(T data) {
	head = _erase(head,data);
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

int main()
{
	AVL<int> tree;
	srand(time(0));
	for (int i = 0; i < 20; i++) tree.insert(rand() % 1000 + 1);
	auto res = tree.sort();
	for (auto& it : res) cout << it << " "; cout << endl;
	int cnt = 0;
	tree.debug();
	for (auto& it : res)  if (!cnt || rand() / double(RAND_MAX) > 0.5) {
		cout << cnt << ": " << it << endl; 
		tree.erase(it); 
		cnt++;
	}
	res = tree.sort();
	for (auto& it : res) cout << it << " "; cout << endl;
	return 0;
}
