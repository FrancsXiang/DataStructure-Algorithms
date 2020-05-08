#include <cstdlib>
#define __THROW_BAD_ALLOC throw std::bad_alloc

class first_allocator
{
private:
	static void* oom_malloc(size_t);
	static void* oom_realloc(void*, size_t);
	static void (*oom_alloc_handler) ();
public:
	static void* allocate(size_t n);
	static void deallocate(void* p);
	static void* reallocate(void* p, size_t n);
	static void (*set_alloc_handler(void (*f) ())) ();
};

void (*first_allocator::oom_alloc_handler) () = 0;

void* first_allocator::allocate(size_t n) {
	void* result = malloc(n);
	if (result == NULL) result = oom_malloc(n);
	return result;
}

void first_allocator::deallocate(void* p) {
	free(p);
}

void* first_allocator::reallocate(void* p, size_t n) {
	void* result = realloc(p, n);
	if (result == NULL) result = oom_realloc(p, n);
	return result;
}

void (*first_allocator::set_alloc_handler(void (*f) ())) () {
	void (*prev) () = oom_alloc_handler;
	oom_alloc_handler = f;
	return prev;
}

void* first_allocator::oom_malloc(size_t n) {
	void* result;
	void (*handler) ();
	while (true) {
		handler = oom_alloc_handler;
		if (handler == 0) __THROW_BAD_ALLOC;
		handler();
		result = malloc(n);
		if (result) return result;
	}
}

void* first_allocator::oom_realloc(void* p, size_t n) {
	void* result;
	void (*handler) ();
	while (true) {
		handler = oom_alloc_handler;
		if (handler == 0) __THROW_BAD_ALLOC;
		handler();
		result = realloc(p,n);
		if (result) return result;
	}
}
