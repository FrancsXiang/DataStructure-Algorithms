/*
Notes:
	You need change the avl.cpp to head file first and delete the main function.
	This is a simple class of Unordered_Set encapsulated by avl tree with string to string elem.(you need add a string field to save value).
	The data_structure of UMP is similar to USet.
	I will finish the red-black-tree version soon! Good Luck!
*/

#include "avl.h" 
#include <string>
using namespace std;

class USet
{
public:
	USet();
	~USet();
	ULL size();
	bool find(string s);
	bool empty();
	void clear();
	void erase(string s);
	void insert(string s);
	string begin();
	string end();
private:
	AVL<ULL> tree;
	ULL Hash(string);
};

USet::USet()
{

}

USet::~USet()
{
	tree.release();
}

//fnv-1a hash
ULL USet::Hash(string s) {
	ULL val = 14695981039346656037ull;
	for (int i = 0; i < s.length(); i++) {
		val ^= (ULL)s[i];
		val *= 1099511628211ull;
	}
	return val;
}

bool USet::find(string s) {
	return tree.search(Hash(s));
}

void USet::clear() {
	tree.release();
}

ULL USet::size() {
	return tree.len;
}

bool USet::empty() {
	return tree.len == 0;
}

string USet::begin() {
	return tree.first_elem();
}

string USet::end() {
	return tree.last_elem();
}

void USet::erase(string s) {
	tree.erase(Hash(s));
}

void USet::insert(string s) {
	return tree.insert(Hash(s), s);
}

int main()
{
	USet test;
	return 0;
}

