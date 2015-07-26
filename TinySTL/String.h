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
		string(size_type n, char c);
		string(const char* s);
		string(const char* s, size_type n);
		string(const string& str);
		string(string&& str);
		string(const string& str, size_t pos, size_type len = npos);
		template <class InputIterator>
		string(InputIterator first, InputIterator last);

		string& operator=(const string& str);
		string& operator=(string&& str);
		string& operator=(const char* s);
		string& operator=(char c);

		~string();

		//迭代器
		iterator begin(){ return start_; }
		iterator end() { return finish_; }
		const_iterator begin() const{ return start_; }
		const_iterator end() const{ return finish_; }
		reverse_iterator rbegin(){ return reverse_iterator(finish_); }
		reverse_iterator rend(){ return reverse_iterator(start_); }
		const_reverse_iterator rbegin() const{ return const_reverse_iterator(finish_); }
		const_reverse_iterator rend() const{ return const_reverse_iterator(start_); }
		const_iterator cbegin() const{ return start_; }
		const_iterator cend() const{ return finish_; }
		const_reverse_iterator crbegin() const{ return const_reverse_iterator(finish_); }
		const_reverse_iterator crend() const{ return const_reverse_iterator(start_); }

		//访问元素
		char& operator[] (size_t pos){ return *(start_ + pos); }
		const char& operator[] (size_t pos) const{ return *(start_ + pos); }
		char& back(){ return *(finish_ - 1); }
		const char& back() const{ return *(finish_ - 1); }
		char& front(){ return *(start_); }
		const char& front() const{ return *(start_); }

		//容量
		size_type size() const{ return finish_ - start_; }
		size_type length() const{ return size(); }
		size_type capacity() const{ return endOfStorage_ - start_; }
		bool empty() const{ return begin() == end(); }

		//修改容器
		
	}
}
#endif