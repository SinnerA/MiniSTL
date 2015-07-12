#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <algorithm>
#include <type_traits>

#include "Allocator.h"
#include "Algorithm.h"
#include "Iterator.h"
#include "ReverseIterator.h"
#include "UninitializedFunctions.h"

namespace TinySTL{
	template <class T, class Alloc = allocator<T>> 
	class vector{
	private:
		T* start_;       //vector��Ԫ��
		T* finish_;      //vectorĩԪ�غ�һ��Ԫ��
		T* endOfStorge_; //�·����ڴ���ĩԪ�غ�һ��Ԫ��

		typedef Alloc dataAllocator;
	public:
		typedef T                            value_type;
		typedef T*                           iterator;
		typedef const T*                     const_iterator;
		//typedef reverse_iterator_t<T*>       reverse_iterator;
		//typedef reverse_iterator_t<const T*> const_reverse_iterator;
		typedef iterator                     pointer;
		typedef T&                           reference;
		typedef const T&                     const_reference;
		typedef size_t                       size_type;
		typedef ptrdiff_t                    difference_type;
	public:
		//���죬���ƣ�������غ���
		vector()
				:start_(0), finish_(0), endOfStorge_(0){ }
		explicit vector(const size_type n);
		explicit vector(const size_type n, const value_type& value);
		vector(const vector& v);
		template <class InputIterator>
		vector(InputIterator begin, InputIterator end);
		vector& operator=(const vector&);
		~vector(){ destoryAndDeallocateAll(); }

		//�Ƚ����
		bool operator==(const vector&);
		bool operator!=(const vector&);

		//���������
		iterator begin(){ return start_; }
		const_iterator begin() const{ return start_; }
		const_iterator cbegin() const{ return start_; }
		iterator end() { return finish_; }
		const_iterator end() const{ return finish_; }
		const_iterator cend() const{ return finish_; }
		iterator rbegin(){ return reverse_iterator(finish_); }
		const_iterator crbegin(){ return const_reverse_iterator(finish_); }
		iterator rend(){ return reverse_iterator(start_); }
		const_iterator crend(){ return const_reverse_iterator(start_); }

		//�������
		difference_type size() const{ return finish_ - start_; }
		difference_type capacity() const{ return endOfStorge_ - start_; }
		bool empty(){ return start_ == finish_; }
		void resize(size_type n, value_type val = value_type());
		void reverse(size_type n);
		void shrink_to_fit();

		//����Ԫ�����
		reference operator[](const difference_type i){ return *(begin() + i); }
		const_reference operator[](const difference_type i) const{ return *(cbegin() + i); }
		reference front(){ return *(begin()); }
		reference back(){ return *(end() - 1); }
		pointer data(){ return start_; }

		//�޸�������ز���
		void clear();
		void push_back(const value_type& val);
		void pop_back();
		void swap(vector& v);
		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, const size_type& n, const value_type& val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		//�����Ŀռ����������
		Alloc get_allocator(){ return dataAllocator; }
	private:
		//�ڴ���乤��
		void destoryAndDeallocateAll();
		void allocateAndFillN(const size_type n, const value_type& value);
		template <class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last);
		template <class InputIterator>
		void vector_aux(InputIterator first, InputIterator last, std::false_type);
		template <class Integer>
		void vector_aux(Integer n, const value_type& value, std::true_type);
		template <class InputIterator>
		void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
		template <class Integer>
		void insert_aux(iterator position, Integer n, const value_type& value, std::true_type);
		template <class InputIterator>
		void reallocateAndCopy(iterator position, InputIterator first, InputIterator last);
		void reallocateAndFillN(iterator position, const size_type& n, const value_type& value);
		size_type getNewCapacity(size_type len) const;
	public:
		template <class T, class Alloc>
		friend bool operator==(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
		template <class T, class Alloc>
		friend bool operator!=(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
	};//end of class vector
}

#include "Detail\Vector.impl.h"
#endif
