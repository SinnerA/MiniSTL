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
		void shrink_to_fit(){ 
			dataAllocator::deallocate(finish_, endOfStorage_ - finish_); 
			endOfStorage_ = finish_;
		}

		void clear(){
			dataAllocator::destroy(start_, finish_);
			start_ = finish_;
		}

		void reserve(size_t n = 0);

		void resize(size_t n);
		void resize(size_t n, char c);

		void push_back(char c){ insert(end(), c); }
		void pop_back(){ erase(end() - 1, end()); }

		string& insert(size_t pos, const string& str);
		string& insert(size_t pos, const string& str, size_t subpos, size_t sublen = npos);
		string& insert(size_t pos, const char* s);
		string& insert(size_t pos, const char* s, size_t n);
		string& insert(size_t pos, size_t n, char c);
		iterator insert(iterator p, size_t n, char c);
		iterator insert(iterator p, char c);
		template <class InputIterator>
		iterator insert(iterator p, InputIterator first, InputIterator last);
		
		string& append(const string& str);
		string& append(const string& str, size_t subpos, size_t sublen = npos);
		string& append(const char* s);
		string& append(const char* s, size_t n);
		string& append(size_t n, char c);
		template <class InputIterator>
		string& append(InputIterator first, InputIterator last);

		string& operator+= (const string& str);
		string& operator+= (const char* s);
		string& operator+= (char c);

		string& erase(size_t pos = 0, size_t len = npos);
		iterator erase(iterator p);
		iterator erase(iterator first, iterator last);

		string& replace(size_t pos, size_t len, const string& str);
		string& replace(iterator i1, iterator i2, const string& str);
		string& replace(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen = npos);
		string& replace(size_t pos, size_t len, const char* s);
		string& replace(iterator i1, iterator i2, const char* s);
		string& replace(size_t pos, size_t len, const char* s, size_t n);
		string& replace(iterator i1, iterator i2, const char* s, size_t n);
		string& replace(size_t pos, size_t len, size_t n, char c);
		string& replace(iterator i1, iterator i2, size_t n, char c);
		template <class InputIterator>
		string& replace(iterator i1, iterator i2, InputIterator first, InputIterator last);

		void swap(string& str){
			TinySTL::swap(start_, str.start_);
			TinySTL::swap(finish_, str.finish_);
			TinySTL::swap(endOfStorage_, str.endOfStorage_);
		}

		size_t copy(char* s, size_t len, size_t pos = 0) const{
			auto ptr = TinySTL::uninitialized_copy(begin() + pos, begin() + pos + len, s);
			return (size_t)(ptr - s);
		}

		string substr(size_t pos = 0, size_t len = npos) const{
			len = changeVarWhenEuqalNPOS(len, size(), pos);
			return string(begin() + pos, begin() + pos + len);
		}

		//查找
		size_t find(const string& str, size_t pos = 0) const;
		size_t find(const char* s, size_t pos = 0) const;
		size_t find(const char* s, size_t pos, size_t n) const;
		size_t find(char c, size_t pos = 0) const;
		size_t rfind(const string& str, size_t pos = npos) const;
		size_t rfind(const char* s, size_t pos = npos) const;
		size_t rfind(const char* s, size_t pos, size_t n) const;
		size_t rfind(char c, size_t pos = npos) const;
		size_t find_first_of(const string& str, size_t pos = 0) const;
		size_t find_first_of(const char* s, size_t pos = 0) const;
		size_t find_first_of(const char* s, size_t pos, size_t n) const;
		size_t find_first_of(char c, size_t pos = 0) const;
		size_t find_last_of(const string& str, size_t pos = npos) const;
		size_t find_last_of(const char* s, size_t pos = npos) const;
		size_t find_last_of(const char* s, size_t pos, size_t n) const;
		size_t find_last_of(char c, size_t pos = npos) const;
		size_t find_first_not_of(const string& str, size_t pos = 0) const;
		size_t find_first_not_of(const char* s, size_t pos = 0) const;
		size_t find_first_not_of(const char* s, size_t pos, size_t n) const;
		size_t find_first_not_of(char c, size_t pos = 0) const;
		size_t find_last_not_of(const string& str, size_t pos = npos) const;
		size_t find_last_not_of(const char* s, size_t pos = npos) const;
		size_t find_last_not_of(const char* s, size_t pos, size_t n) const;
		size_t find_last_not_of(char c, size_t pos = npos) const;

		//比较
		int compare(const string& str) const;
		int compare(size_t pos, size_t len, const string& str) const;
		int compare(size_t pos, size_t len, const string& str,
			size_t subpos, size_t sublen = npos) const;
		int compare(const char* s) const;
		int compare(size_t pos, size_t len, const char* s) const;
		int compare(size_t pos, size_t len, const char* s, size_t n) const;
	private:
		void moveData(string& str);
		//插入时空间不足的情况
		template<class InputIterator>
		iterator insert_aux_copy(iterator p, InputIterator first, InputIterator last);
		//插入时空间不足的情况
		iterator insert_aux_filln(iterator p, size_t n, value_type c);
		size_type getNewCapacity(size_type len)const;
		void allocateAndFillN(size_t n, char c);
		template<class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last);
		void string_aux(size_t n, char c, std::true_type);
		template<class InputIterator>
		void string_aux(InputIterator first, InputIterator last, std::false_type);
		void destroyAndDeallocate();
		size_t rfind_aux(const_iterator cit, size_t pos, size_t lengthOfS, int cond)const;
		size_t find_aux(const_iterator cit, size_t pos, size_t lengthOfS, size_t cond)const;
		int compare_aux(size_t pos, size_t len, const_iterator cit, size_t subpos, size_t sublen)const;
		bool isContained(char ch, const_iterator first, const_iterator last)const;
		size_t changeVarWhenEuqalNPOS(size_t var, size_t minuend, size_t minue)const;
	public:
		friend std::ostream& operator <<(std::ostream& os, const string&str);
		friend std::istream& operator >> (std::istream& is, string& str);
		friend string operator+ (const string& lhs, const string& rhs);
		friend string operator+ (const string& lhs, const char* rhs);
		friend string operator+ (const char* lhs, const string& rhs);
		friend string operator+ (const string& lhs, char rhs);
		friend string operator+ (char lhs, const string& rhs);
		friend bool operator== (const string& lhs, const string& rhs);
		friend bool operator== (const char*   lhs, const string& rhs);
		friend bool operator== (const string& lhs, const char*   rhs);
		friend bool operator!= (const string& lhs, const string& rhs);
		friend bool operator!= (const char*   lhs, const string& rhs);
		friend bool operator!= (const string& lhs, const char*   rhs);
		friend bool operator<  (const string& lhs, const string& rhs);
		friend bool operator<  (const char*   lhs, const string& rhs);
		friend bool operator<  (const string& lhs, const char*   rhs);
		friend bool operator<= (const string& lhs, const string& rhs);
		friend bool operator<= (const char*   lhs, const string& rhs);
		friend bool operator<= (const string& lhs, const char*   rhs);
		friend bool operator>  (const string& lhs, const string& rhs);
		friend bool operator>  (const char*   lhs, const string& rhs);
		friend bool operator>  (const string& lhs, const char*   rhs);
		friend bool operator>= (const string& lhs, const string& rhs);
		friend bool operator>= (const char*   lhs, const string& rhs);
		friend bool operator>= (const string& lhs, const char*   rhs);
		friend void swap(string& x, string& y);
		friend std::istream& getline(std::istream& is, string& str, char delim);
		friend std::istream& getline(std::istream& is, string& str);
	}
}
#endif