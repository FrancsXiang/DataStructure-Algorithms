/*
Notes:
	You need change the avl.cpp to head file first and delete the main function.
	This is a simple class of Map encapsulated by avl tree with string to string elem.(you need add a string field to save value).
	The data_structure of Map is similar to Set.
	You could use template features to make the (key,val) pair more flexible!
	And you only need to overload key operators(>/</==) for complicated types.
	I will finish the red-black-tree version soon! Good Luck!
*/

#include "avl.h" 
#include <string>
using namespace std;

class Map
{
public:
	~Map();
	ULL size();
	bool find(string);
	bool empty();
	void clear();
	void erase(string);
	void insert(string, string);
	vector<pair<string, string>> sort();
	string begin();
	string end();
	//TODO next two function just apply b_search
	//string lower_bound(string s); (first string res >= s) 
	//string upper_bound(string s); (first string res > s)
private:
	AVL<string> tree;
	ULL Hash(string);
};

Map::~Map()
{
	tree.release();
}

//fnv-1a hash
ULL Map::Hash(string s) {
	ULL val = 14695981039346656037ull;
	for (int i = 0; i < s.length(); i++) {
		val ^= (ULL)s[i];
		val *= 1099511628211ull;
	}
	return val;
}

bool Map::find(string s) {
	return tree.search(s);
}

void Map::clear() {
	tree.release();
}

ULL Map::size() {
	return tree.len;
}

bool Map::empty() {
	return tree.len == 0;
}

string Map::begin() {
	return tree.first_elem();
}

string Map::end() {
	return tree.last_elem();
}

void Map::erase(string s) {
	tree.erase(s);
}

void Map::insert(string key, string val) {
	return tree.insert(key, val);
}

vector<pair<string, string>> Map::sort() {
	return tree.sort();
}

int main()
{
	Map mp;
	srand(time(0));
	for (int i = 0; i < 10; i++) mp.insert(string(1, 'a' + i), string(1, 'a' + i + 1));
	auto res = mp.sort();
	for (auto& it : res) cout << it.first << " " << it.second << endl;
	cout << endl;
	for (int i = 0; i < 10; i++) if (rand() / (double)RAND_MAX > 0.5) mp.erase(string(1, 'a' + i));
	res = mp.sort();
	for (auto& it : res) cout << it.first << " " << it.second << endl;
	return 0;
}

