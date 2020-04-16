#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

template<typename T>
struct node {
	int cnt;
	node<T>* l, * r;
	node<T>(int c) : cnt(c), l(NULL), r(NULL) {}
};

template<typename T>
class HFT
{
public:
	HFT(vector<T>&);
	~HFT();
	string get_code(T);
private:
	struct cmp {
		bool operator()(node<T>*& a, node<T>*& b) {
			return a->cnt > b->cnt;
		}
	};
	vector<T> container;
	priority_queue<node<T>*, vector<node<T>*>, cmp> list;
	unordered_map<T, string> res;
	unordered_map<T, int> cnt;
	unordered_map<node<T>*, T> hash;
	void build();
	void search(node<T>* root, string str);
};

template<typename T>
HFT<T>::HFT(vector<T>& container)
{
	if (container.size() < 2) throw "sequence length must more than one!";
	this->container = container;
	build();
}

template<typename T>
HFT<T>::~HFT()
{
	container.clear();
	res.clear();
	cnt.clear();
	hash.clear(); 
}

template<typename T>
void HFT<T>::build() {
	for (auto& it : container) cnt[it]++;
	for (auto& it : cnt) {
		auto p = new node<T>(it.second);
		hash[p] = it.first;
		list.push(p);
	}
	//throw "stop test";
	while (list.size() != 1) {
		auto s1 = list.top(); list.pop();
		auto s2 = list.top(); list.pop();
		auto p = new node<T>(s1->cnt + s2->cnt);
		if (s1->cnt < s2->cnt) {
			p->l = s1; p->r = s2;
		}
		else {
			p->l = s2; p->r = s1;
		}
		list.push(p);
	}
	auto root = list.top();
	list.pop();
	search(root, "");
}

template<typename T>
void HFT<T>::search(node<T>* root, string str) {
	if (!root->l && !root->r) {
		res[hash[root]] = str;
		return;
	}
	search(root->l, str+"0"); search(root->r,str+"1");
}

template<typename T>
string HFT<T>::get_code(T val) {
	return res[val];
}

int main()
{
	srand(time(0));
	vector<char> orgin;
	for (int i = 0; i < 2; i++) orgin.push_back(rand() % 26 + 'A');
	try
	{
		HFT<char> tree(orgin);
		for (auto& it : orgin) cout << it << " " << tree.get_code(it) << endl;
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
	}
	return 0;
}
