#include <iostream>
#include <cstdio>
using namespace std;

template<typename T>
class Item
{
public:
	Item(T _val) :val(_val), next(NULL) {};
	T get_val() const { return val; }
	Item<T>*& get_next() { return next; }
private:
	T val;
	Item<T>* next;
};

template<typename T>
class List
{
public:
	void insert_front(T value);
	void insert_back(T value);
	void display(std::ostream& os = std::cout) const;
	Item<T>* get_front() const { return begin; }
private:
	Item<T>* begin, * end;
	size_t length;
};

template<typename T>
void List<T>::insert_front(T value) {
	if (length == 0) begin = end = new Item<T>(value);
	else {
		auto ptr = new Item<T>(value);
		ptr->get_next() = begin;
		begin = ptr;
	}
	length++;
}

template<typename T>
void List<T>::insert_back(T value) {
	if (length == 0) begin = end = new Item<T>(value);
	else {
		end->get_next() = new Item<T>(value);
		end = end->get_next();
	}
	length++;
}

template<typename T>
void List<T>::display(std::ostream& os) const {
	Item<T>* cur = begin;
	while (cur) {
		os << cur->get_val() << " ";
		cur = cur->get_next();
	}
	cout << endl;
}

template<typename T>
struct Iter {
	typedef T value_type;
	T* ptr;
	Iter(T* p = 0) : ptr(p) {};
	T& operator*() const { return *ptr; }
	T* operator->() const { return ptr; }
	Iter& operator++() { ptr = ptr->get_next(); return *this; }
	Iter operator++(int) { Iter tmp = *this; ++* this; return tmp; }
	bool operator==(const Iter& other) { return ptr == other.ptr; }
	bool operator!=(const Iter& other) { return ptr != other.ptr; }
};

template<typename T>
bool operator==(const Item<T>& item, T val) {
	return item.get_val() == val;
}

template<typename InputIterator, typename T>
InputIterator search(InputIterator first, InputIterator last, const T val) {
	while (first != last) {
		if (*first == val) break;
		first++;
	}
	return first;
}

template<typename I>
struct iterator_traits_ {
	typedef typename I::value_type value_type;
};

template<typename T>
struct iterator_traits_<T*> {
	typedef T value_type;
};

template<typename T>
struct iterator_traits_<const T*> {
	typedef T value_type;
};

template<typename I>
typename iterator_traits_<I>::value_type func(I it) {
	return *it;
}


int main()
{
	List<int> list;
	for (int i = 0; i < 10; i++) {
		list.insert_back(i);
		list.insert_front(2 * i);
	}
	list.display();
	Iter<Item<int>> begin(list.get_front());
	Iter<Item<int>> end;
	auto iter = search(begin, end, 18);
	if (iter == end) cout << "no elem found!" << endl;
	else cout << "elem found: " << iter->get_val() << endl;
	cout << func(begin).get_val() << endl;
	return 0;
}
