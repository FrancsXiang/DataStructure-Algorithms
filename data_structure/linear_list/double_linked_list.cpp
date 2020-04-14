/*
This is a totaly oop implementation of data_structure of double_linked_list which looks more standard and beautiful.
*/
#include <iostream>
#include <cstdio>
using namespace std;

template<typename T>
struct node {
	T data;
	node<T> *l,*r;
	node<T>() :l(NULL), r(NULL) {}
};

template<typename T>
class DLL {
	public:
		int len;
		node<T>* head;
		DLL();
		~DLL();
		int get_length();
		node<T>* get_prev(node<T>* site);
		node<T>* get_next(node<T>* site);
		void insert(int val, int index);
		T erase(int index);
		void show_list();
};

template<typename T>
DLL<T>::DLL() {
	len = 0;
	head = new node<T>;
	head->r = NULL;
}

template<typename T>
DLL<T>::~DLL() {
	node<T>* cur = head->r;
	delete head;
	while (cur) {
		if (cur->r) {
			cur = cur->r;
			delete cur->l;
		}
		else {
			delete cur;
			cur = NULL;
		}
	}
}

template<typename T>
int DLL<T>::get_length() {
	return len;
}

template<typename T>
node<T>* DLL<T>::get_prev(node<T>* site) {
	return site->l;
}

template<typename T>
node<T>* DLL<T>::get_next(node<T>* site) {
	return site->r;
}

template<typename T>
void DLL<T>::insert(int val, int index) {
	node<T>* p = new node<T>;
	p->data = val;
	node<T>* cur = head;
	if (index<0 || index>len) throw "index out of range!";
	if (len == 0) head->r = p;
	else {
		for (int i = 0; i < index; i++) cur = cur->r;
		if (index == 0) {
			p->r = head->r;
			head->r->l = p;
			head->r = p;
		}
		else if (index == len) {
			cur->r = p;
			p->l = cur;
		}
		else {
			p->r = cur->r;
			cur->r->l = p;
			cur->r = p;
			p->l = cur;
		}
	}
	len++;
}

template<typename T>
T DLL<T>::erase(int index) {
	T val;
	node<T>* cur = head;
	if (index<0 || index>=len|| len == 0) throw "index out of range!";
	if (len == 1) {
		val = head->r->data;
		delete head->r;
		head->r = NULL;
	}
	else {
		for (int i = 0; i < index; i++) cur = cur->r;
		if (index == 0) {
			head->r = head->r->r;
			val = head->r->l->data;
			delete head->r->l;
			head->r->l = NULL;
		}
		else if (index == len - 1) {
			val = cur->r->data;
			delete cur->r;
			cur->r = NULL;
		}
		else {
			cur->r = cur->r->r;
			val = cur->r->l->data;
			delete cur->r->l;
			cur->r->l = cur;
		}
	}
	len--;
	return val;
}

template<typename T>
void DLL<T>::show_list() {
	node<T>* cur = head->r;
	while (cur) {
		cout << cur->data << " ";
		cur = cur->r;
	}
	cout << endl;
}

int main()
{
	int val;
	DLL<int> list;
	for(int i=0;i<10;i++) list.insert(i, 0);
	try
	{
		val = list.erase(2);
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
	}
	list.show_list();
	return 0;
}
