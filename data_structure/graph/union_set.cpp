#include <iostream>
#include <unordered_map>
using namespace std;

template<typename T> 
class US
{
public:
	void insert(T);
	void Union(T, T);
	bool is_common_set(T, T);
	T find(T);
private:
	unordered_map<T, T> f;
};

template<typename T>
void US<T>::insert(T item) {
	f[item] = item;
}

template<typename T>
T US<T>::find(T x) {
	if (x != f[x]) return f[x] = find(f[x]);
	else return x;
}

template<typename T>
void US<T>::Union(T x, T y) {
	T fx = find(x);
	T fy = find(y);
	if (fx != fy) return f[fx] = fy;
}

template<typename T>
bool US<T>::is_common_set(T x, T y) {
	return find(x) == find(y);
}

int main()
{
	//when the T is a class-type or struct,you need overload the corresponding operators.
	US<int> set;
	set.insert(1);
	set.insert(2);
	return 0;
}
