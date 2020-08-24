#include "first_alloc.h"

//object section block size is fixed with n which is times of low_bytes.
enum {
	up_bytes = 128,
	low_bytes = 8,
	n_lists = up_bytes / low_bytes
};

class sec_allocator
{
private:
	static size_t round_up(size_t n);
	static size_t lists_offset(size_t n);
	union node { //node's size takes 8 bytes <= low_bytes which could be feasible,union_struct saves the memory.
		union node* next;
		char data[1];
	};
	static node* volatile lists[n_lists];
	static char* start;
	static char* end;
	static size_t heap_size;
public:
	static void* allocate(size_t n);
	static void deallocate(void* p, size_t n);
	static void* reallocate(void* p, size_t old_size, size_t new_size);
	static void* refill(size_t n, size_t blocks = 20);
	static char* block_alloc(size_t n, size_t& block);
};

char* sec_allocator::start = 0;
char* sec_allocator::end = 0;
size_t sec_allocator::heap_size = 0;
sec_allocator::node* volatile sec_allocator::lists[n_lists] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

size_t sec_allocator::round_up(size_t n) {
	//lower_bytes must be 2^n
	//return val, ceil(val) == k * lower_bytes(k>=1).
	return ((n + low_bytes - 1) & ~(low_bytes - 1));
}

size_t sec_allocator::lists_offset(size_t n) {
	return	(n + low_bytes - 1) / low_bytes - 1;
}

void* sec_allocator::allocate(size_t n) {
	node* volatile* cur_list;
	node* result;
	n = round_up(n);
	if (n > (size_t)up_bytes) return first_allocator::allocate(n);
	cur_list = lists + lists_offset(round_up(n));
	result = *cur_list;
	if (result == NULL) return (void*)refill(round_up(n)); //There is no more space to allocate.
	*cur_list = result->next;
	return result;
}

void sec_allocator::deallocate(void* p, size_t n) {
	node* cur = (node*)p;
	node* volatile* cur_list;
	n = round_up(n);
	if (n > (size_t)up_bytes) { first_allocator::deallocate(p); return; }
	cur_list = lists + lists_offset(n);
	cur->next = *cur_list;
	*cur_list = cur;
}

void* sec_allocator::refill(size_t n, size_t blocks=20) { //refill the lists space and return one section block.
	node* result, * cur, * next;
	node* volatile* cur_list;
	char* cur_block = block_alloc(n, blocks);
	if (blocks == 1) return cur_block;
	cur_list = lists + lists_offset(n);
	result = (node*)cur_block;
	*cur_list = next = (node*)(cur_block + n);
	for (int i = 0; i < blocks - 2; i++) { // link the rest of the block sections.
		cur = next;
		next = (node*)((char*)cur + n);
		cur->next = next;
	}
	next->next = NULL;
	return result;
}

char* sec_allocator::block_alloc(size_t n, size_t& blocks) { //get several block sections from memory pool.
	char* result;
	size_t need = n * blocks;
	size_t rest = end - start;
	node* volatile* cur_list;
	node* cur;
	if (rest >= need) {
		result = start;
		start += need;
		return result;
	}
	else if (rest >= n) {
		blocks = rest / n; // recitify the num of blocks
		need = n * blocks;
		result = start;
		start += need;
		return result;
	}
	else {
		need = 2 * need + round_up(heap_size >> 4);
		if (rest > 0) { //puts the rest of memory pool to lists.
			cur_list = lists + lists_offset(rest); //rest should be times of low_bytes.
			((node*)start)->next = *cur_list;
			*cur_list = (node*)start;
		}
		start = (char*)malloc(need);
		if (start == NULL) { //malloc fail,try to search bigger block section.
			for (int i = n; i <= up_bytes; i += low_bytes) {
				cur_list = lists + lists_offset(i);
				cur = *cur_list;
				if (cur) {
					*cur_list = cur->next;
					start = (char*)cur;
					end = start + i;
					return block_alloc(n, blocks);
				}
			}
		}
		start = (char*)first_allocator::allocate(need);// call first_allocator to handle.
		heap_size += need;
		end = start + need;
		return block_alloc(n, blocks);
	}
}

//due to memory consecution,so you can't use realloc directly which could destroy the memory pool.
void* sec_allocator::reallocate(void* p, size_t old_size, size_t new_size) {
	old_size = round_up(old_size);new_size = round_up(new_size);
	if (old_size > up_bytes && new_size > up_bytes) return first_allocator::reallocate(p, new_size);
	if (old_size == new_size) return p;
	void* result = allocate(new_size);
	size_t copy_size = new_size > old_size ? old_size : new_size;
	memcpy(result, p, copy_size);
	deallocate(p, old_size);
	return result;
}
