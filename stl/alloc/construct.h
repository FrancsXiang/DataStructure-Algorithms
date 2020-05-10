#include <new>

template<typename T1, typename T2>
inline void construct(T1* p, const T2& value) {
	new ((void*)p) T1(value);
}

template<typename T1, typename T2>
inline void construct(T1* p) {
	new ((void*)p) T1();
}


template<typename T>
inline void destroy(T* pointer) {
	pointer->~T();
}

inline void destroy(char*,char*) {}
inline void destroy(int*, int*) {}
inline void destroy(long*, long*) {}
inline void destroy(float*, float*) {}
inline void destroy(double*, double*) {}
inline void destroy(wchar_t*,wchar_t*) {}

struct __true_type {};
struct __false_type {};

template<typename Iterator>
struct iterator_traits_ {
	typedef typename Iterator::value_type value_type;
};

template<typename T>
struct iterator_traits_<T*> {
	typedef typename T value_type;
};

template<typename T>
struct iterator_traits_<const T*> {
	typedef typename T value_type;
};

template<typename T>
struct __type_traits_ {
	typedef typename __false_type has_trivial_destructor;
};

template<>
struct __type_traits_<char>{ //POD type example.
	typedef typename __true_type has_trivial_destructor;
};

template<typename forward_iterator>
inline void destroy(forward_iterator first, forward_iterator last) {
	__destroy(first, last, iterator_traits_<first>::value_type());
}

template<typename forward_iterator, typename T>
inline void __destroy(forward_iterator first, forward_iterator last, T) {
	typedef typename __type_traits_<T>::has_trivial_destructor _Trivial_destructor;
	__destroy_aux(first, last, _Trivial_destructor());
}

template<typename forward_iterator>
inline void __destroy_aux(forward_iterator first, forward_iterator last, __false_type) {
	while (first != last) {
		destroy(&*first);
		first++;
	}
}

template<typename forward_iterator>
inline void __destroy_aux(forward_iterator first, forward_iterator last, __true_type) {}

