#include <iostream>
#include <map>
#include <vector>
#include <unordered_set>
#define PART 0
#define ALL 1
using namespace std;

struct node
{
	int cnt;
	map<char, node*> next;
};

class Trie
{
public:
	Trie();
	~Trie();
	void insert(string);
	int find(string, int code = ALL);
	vector<string> sort();
private:
	node* head;
	vector<string> res;
	unordered_set<node*> flag;
	void pre_order(node*, string);
	void clear_all(node*);
};

Trie::Trie()
{
	head = new node();
}

Trie::~Trie()
{
	clear_all(head);
}

void Trie::insert(string s) {
	node* cur = head;
	for (int i = 0; i < s.length(); i++) {
		if (!cur->next.count(s[i])) cur->next[s[i]] = new node();
		cur = cur->next[s[i]];
		cur->cnt++;
	}
	flag.insert(cur);
}

int Trie::find(string s, int code) {
	node* cur = head;
		for (int i = 0; i < s.length(); i++) {
			if (!cur->next.count(s[i])) return 0;
			cur = cur->next[s[i]];
		}
	if (code == PART) return cur->cnt;
	else if (!flag.count(cur)) return 0;
	else return 1;
}

vector<string> Trie::sort() {
	pre_order(head, "");
	return res;
}

void Trie::pre_order(node* root, string s) {
	if (root) {
		if (flag.count(root)) res.push_back(s);
		for (auto& it : root->next) {
			s.push_back(it.first);
			pre_order(it.second, s);
			s.pop_back();
		}
	}
}

void Trie::clear_all(node* root) {
	if (root) {
		for (auto& it : root->next) clear_all(it.second);
		delete root;
	}
}

int main()
{
	Trie tree;
	vector<string> res;
	tree.insert("abc");
	tree.insert("acb");
	tree.insert("a");
	tree.insert("abd");
	//cout << tree.find("a",PART) << endl;
	res = tree.sort();
	for (auto& it : res) cout << it << endl;
	return 0;
}
