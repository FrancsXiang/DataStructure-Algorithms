/*
 This is a implementation of data_structure of priority_queue (max heap with linked list & generics supported!)
*/
#include <iostream>
#include <vector>
#define Left 0
#define Right 1
using namespace std;

template<typename T>
struct node
{
	T data;
	node<T>* prev, * l, * r;
	node<T>() : prev(NULL), l(NULL), r(NULL) {}
};

template<typename T>
class PQ
{
public:
	PQ();
	~PQ();
	T front();
	void pop();
	void push(int val);
private:
	int len;
	node<T>* tree;
	vector<int> seq;
	void get_seq(int n);
	node<T>* find_node(int cur, node<T>* root);
	void clear_all(node<T>* root);
	void up_adjust(node<T>* root);
	void down_adjust(node<T>* root);
	void show_tree_list(node<T>* root=tree);
};

template<typename T>
PQ<T>::PQ()
{
	tree = NULL;
	len = 0;
}

template<typename T>
PQ<T>::~PQ()
{
	show_tree_list(tree);
	clear_all(tree);
}

template<typename T>
T PQ<T>::front() {
	if (len == 0) throw "no elements in queue!";
	return tree->data;
}

template<typename T>
void PQ<T>::get_seq(int n) {
	seq.clear();
	while (n != 1) {
		if (n % 2 == 0) seq.push_back(Left);
		else seq.push_back(Right);
		n /= 2;
	}
	reverse(seq.begin(), seq.end());
}

template<typename T>
node<T>* PQ<T>::find_node(int cur, node<T>* root) {
	if (cur == seq.size()) {
		return root;
	}
	else {
		if (seq[cur] == Left) return find_node(cur + 1, root->l);
		else return find_node(cur + 1, root->r);
	}
}

template<typename T>
void PQ<T>::push(int val) {
	if (len == 0) {
		tree = new node<T>;
		tree->data = val;
	}
	else {
		get_seq((len + 1) / 2);
		node<T>* prev = find_node(0, tree);
		node<T>* p = new node<T>;
		p->data = val;
		if ((len + 1) % 2 == 0) prev->l = p;
		else prev->r = p;
		p->prev = prev;
		up_adjust(p);
	}
	len++;
}

template<typename T>
void PQ<T>::pop() {
	if (len == 0) throw "no elements in queue!";
	if (len == 1) {
		delete tree;
		tree = NULL;
	}
	else {
		get_seq(len);
		node<T>* last = find_node(0, tree);
		swap(last->data, tree->data);
		last = last->prev;
		if (len % 2 == 0) {
			delete last->l;
			last->l = NULL;
		}
		else {
			delete last->r;
			last->r = NULL;
		}
		down_adjust(tree);
	}
	len--;
}

template<typename T>
void PQ<T>::up_adjust(node<T>* root) {
	if (root->prev) {
		if (root->data > root->prev->data) {
			swap(root->data, root->prev->data);
			up_adjust(root->prev);
		}
	}
}

template<typename T>
void PQ<T>::down_adjust(node<T>* root) {
	if (root) {
		node<T>* p = root;
		if (root->l && root->l->data > p->data) p = root->l;
		if (root->r && root->r->data > p->data) p = root->r;
		if (p != root) {
			swap(root->data, p->data);
			down_adjust(p);
		}
	}
}

template<typename T>
void PQ<T>::clear_all(node<T>* root) {
	if (root) {
		clear_all(root->l); clear_all(root->r);
		delete root;
	}
}

template<typename T>
void PQ<T>::show_tree_list(node<T>* root) {
	if (root) {
		cout << root->data << " ";
		show_tree_list(root->l); show_tree_list(root->r);
	}
}

int main()
{
	PQ<int> que;
	for (int i = 0; i < 20; i++) que.push(i);
	try
	{
		que.push(100);
		for (int i = 0; i < 20; i++) {
			cout << que.front() << " ";
			que.pop();
		}
		cout << endl;
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
	}
	return 0;
}
