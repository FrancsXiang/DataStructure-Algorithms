#include <new>

template<class T1, class T2>
inline void construct(T1* p, const T2& value) {
	new ((void*)p) T1(value);
}

template<class T1, class T2>
inline void construct(T1* p, const T2& value) {
	new ((void*)p) T1();
}


template<class T>
inline void destroy(T* pointer) {
	pointer->~T();
}

inline void destroy(char*,char*) {}
inline void destroy(int*, int*) {}
inline void destroy(long*, long*) {}
inline void destroy(float*, float*) {}
inline void destroy(double*, double*) {}
inline void destroy(wchar_t*,wchar_t*) {}

template<class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
	__destroy(first, last, value_type(first));
}

template<class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*) {
	typedef typename __type_traits_<T>::has_trivial_destructor _Trivial_destructor;
	__destroy_aux(first, last, _Trivial_destructor());
}

template<class ForwardIterator>
inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __false_type) {
	while (first != last) {
		destroy(&*first);
		first++;
	}
}

template<class ForwardIterator>
inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __true_type) {}
