#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename T, typename C>
class Iterator {
public:
	typedef typename vector<T>::iterator iter_type;
	Iterator(C* container_) : container(container_) { iter = container->m_data.begin();}
	iter_type begin() { return container->m_data.begin(); }
	iter_type next() { return ++iter; }
	iter_type cur() { return iter; }
	bool end() { return iter == container->m_data.end(); }
private:
	iter_type iter;
	C* container;
};

template<typename T>
class Container {
public:
	friend class Iterator<T, Container>;
	void add(T data) { m_data.push_back(data); }
	Iterator<T, Container>* create_iterator() { return new Iterator<T, Container>(this); }

private:
	vector<T> m_data;
};

class Data {
public:
	Data(int a = 0) : m_data(a) {}
	int data() { return m_data; }
	void set_data(int data) { m_data = data; }
	friend ostream& operator<< (ostream& os, Data& data) { return os << data.m_data; }
private:
	int m_data;
};

void client() {
	Data a(100), b(20), c(-3);
	Container<Data> container;
	container.add(a);
	container.add(b);
	container.add(c);
	auto iter = container.create_iterator();
	for (; !iter->end(); iter->next()) cout << iter->cur()->data() << endl;
}

int main()
{
	client();
	return 0;
}
