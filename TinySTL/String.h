#ifndef _STRING_H_
#define _STRING_H_

#include <cstring>
#include <type_traits>

#include "Allocator.h"
#include "ReverseIterator.h"
#include "UninitializedFunctions.h"
#include "Utility.h"

namespace TinySTL{
	class string{
	public:
		typedef char                                   value_type;
		typedef char*                                  iterator;
		typedef const char*                            const_iterator;
		typedef reverse_iterator_t<char*>              reverse_iterator;
		typedef reverse_iterator_t<const char*>        const_reverse_iterator;
		typedef char&                                  reference;
		typedef const char&                            const_reference;
		typedef size_t                                 size_type;
		typedef ptrdiff_t                              difference_type;
		static const size_t npos = -1;
	private:
		char *start_;
		char *finish_;
		char *endOfStorge_;
		typedef TinySTL::allocator<char> dataAllocator;
	public:
		//构造，拷贝赋值和析构
		string():start_(0), finish_(0), endOfStorge_(0){}
		string(size_t n, char c);
		string(const char* s);
		string(const char* s, size_t n);
		string(const string& str);
		string(string&& str);
		string(const string& str, size_t pos, size_t len = npos);
		template <class InputIterator>
		string(InputIterator first, InputIterator last);

		string& operator=(const string& str);
		string& operator=(string&& str);
		string& operator=(const char* s);
		string& operator=(char c);

		~string();

		//迭代器
	}
}
#endif