#ifndef CPPUTIL_INCLUDE_ALLOCATOR_ALIGNED_H
#define CPPUTIL_INCLUDE_ALLOCATOR_ALIGNED_H

#include <cassert>
#include <cstdlib>
#include <stddef.h>

#include <limits>

template <typename T, size_t N = 16>
class Aligned {
	public:
		typedef T value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		typedef T* pointer;
		typedef const T* const_pointer;

		typedef T& reference;
		typedef const T& const_reference;

		template <typename T2>
		struct rebind {
			typedef Aligned<T2, N> other;
		};

		explicit Aligned() { }
		~Aligned() { }
		explicit Aligned(const Aligned& rhs) { }
		template<typename T2>
		explicit Aligned(const Aligned<T2>& rhs) { }

		pointer address (reference r) {
			return &r;
		}

		const_pointer address (const_reference r) const {
			return &r;
		}

		pointer allocate(size_type n, typename std::allocator<void>::const_pointer = 0) {
			void* p = nullptr;

			const auto res = posix_memalign(&p, N, n*sizeof(value_type));
			assert(res == 0);

			return (pointer)p;
		}

		void deallocate(pointer p, size_type) {
			free(p);
		}

		size_type max_size() const {
			return std::numeric_limits<size_type>::max() / sizeof(T);
		}

		void construct(pointer p, const value_type& t) {
			new(p) value_type(t);
		}
		void destroy(pointer p) {
			p->~value_type ();
		}

		bool operator==(const Aligned<T,N>& rhs) const {
			return true;
		}
		bool operator!=(const Aligned<T,N>& rhs) const  {
			return !(*this == rhs);
		}
};

#endif
