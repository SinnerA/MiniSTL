#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <algorithm>
#include <memory>
#include <cstddef>

namespace TinySTL{
	template <class T, class Alloc = alloctor<T>> 
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
		typedef reverse_iterator_t<T*>       reverse_iterator;
		typedef reverse_iterator_t<const T*> const_reverse_iterator;
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
		vector(InputItertor begin, InputIterator end);
		vector& operator=(const vector&);
		~Vecotor(){ destoryAndDeallocateAll(); }

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
		void shrink_to_fit(){
			dataAllocator::deallocate(finish_, endOfStorge_ - finish_);
			endOfStorge_ = finish_;
		}

		//����Ԫ�����
		value_type& operator[](const difference_type i){ return *(begin() + i); }
		value_type& front(){ return *(begin()); }
		value_type& back(){ return *(end() - 1); }
		pointer data(){ return start_; }

		//�޸�������ز���
		void clear(){
			//��������Ԫ�أ��������տռ�
			dataAllocator::destory(start_, finish_);
			finish_ = start_;
		}
		void push_back(const value_type& val);
		void pop_back(){
			--finish_;
			dataAllocator::destory(finish_);
		}
		void swap(vector& v){
			if(&v != this){
				TinySTL::swap(start_, v.start_);
				TinySTL::swap(finish_, v.finish_);
				TinySTL::swap(endOfStorge_, v.endOfStorge_);
			}
		}
		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, const size_type n, const type_value& val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		//�����Ŀռ����������
		Alloc get_allocator(){ return dataAllocator; }
	private:
		//�ڴ���乤��
		void destoryAndDeallocateAll(){
			if(capacity() != 0){
				dataAllocator::destory(start_, finish_);
				dataAllocator::deallocate(start_, endOfStorge_ - start_);
			}
		}
		void allocateAndFillN(const size_type n, const value_type& value){
			start_ = dataAllocator::allocate(n);
			finish_ = endOfStorge_ = start_ + n;
			dataAllocator::uninitialized_fill(start_, finish_, value);
		}
		template <class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last){
			start_ = dataAllocator::allocate(last - first);
			finish_ = dataAllocator::uninitialized_copy(first, last, start_);
			endOfStorge_ = finish_;
		}

		template <class InputIterator>
		void vector_aux(InputIterator first, InputIterator last, std::false_type){
			allocateAndCopy(first, last);
		}
		template <class Integer>
		void vector_aux(Integer n, const value_type& value, std::true_type){
			allocateAndFillN(n, value);
		}
		template <class InputIterator>
		void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
		template <class Integer>
		void insert_aux(iterator position, Integer n, const value_type& value, std::true_type);
		template <class InputIterator>
		void reallocateAndCopy(iterator position, InputIterator first, InputIterator last);
		void reallocateAndFillN(iterator position, const size_type& n, const value_type& value);
		size_type getNewCapacity(size_type len){
			size_type oldCapacity = endOfStorge_ - start_;
			auto res = TinySTL::max(oldCapacity, len);
			size_type newCapacity  = oldCapacity != 0 ? (oldCapacity + res) : len;
			return newCapacity;
		}
	public:
		template <class T, class Alloc>
		friend bool operator==(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
		template <class T, class Alloc>
		friend bool operator!=(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
	};//end of class vector

	//---------------------------���죬���ƣ�������غ���-----------------------------
	template <class T, class Alloc>
	vector<T, Alloc>::vector(const size_type n){
		allocateAndFillN(n, value_type());
	}
	template <class T, class Alloc>
	vector<T, Alloc>::vector(const size_type n, const value_type& value){
		allocateAndFillN(n, value);
	}
	template <class T, class Alloc>
	vector<T, Alloc>::vector(const vector& v){
		allocateAndCopy(v.start_, v.finish_);
	}
	template <class T, class Alloc>
	template <class InputIterator>
	vector<T, Alloc>::vector(InputItertor begin, InputIterator end){
		//����ָ������ּ������ĺ���
		vector_aux(begin, end, typename std::is_integral<InputItertor>::type());
	}
	template <class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& v){
		if(&rhs != this){
			destoryAndDeallocateAll();
			allocateAndCopy(rhs.start_, rhs.finish_);
		}
		return *this;
	}

	//---------------------------�����������-----------------------------
	template <class T, class Alloc>
	void vector<T, Alloc>::resize(size_type n, value_type val = value_type()){
		if(n < size()){
			dataAllocator::destory(finish_, n - size());
			finish_ = start_ + n;
		} else if(n > size() && n < capacity()){
			size_type lengthOfInsert = n - size();
			finish_ = uninitialized_fill_n(finish_, lengthOfInsert, val);
		} else if(n > capacity()){
			size_type lengthOfInsert = n - size();
			T* newStart = dataAllocator::allocate(getCapacity(lengthOfInsert));
			T* newFinish = TinySTL::uninitialized_copy(begin(), end(), newStart);
			newFinish = TinySTL::uninitialized_fill_n(newFinish, lengthOfInsert, val);

			destoryAndDeallocateAll();
		
			start_ = newStart;
			finish_ = newFinish;
			endOfStorge_ = start_ + n;
		}
	}
	template <class T, class Alloc>
	void vector<T, Alloc>::reverse(size_type n){
		if(n < capacity())
			return;
		T* newStart = dataAllocator::allocate(n);
		T* newFinish = TinySTL::uninitialized_copy(begin(), end(), newStart);

		destoryAndDeallocateAll();

		start_ = newStart;
		finish_ = newFinish;
		endOfStorge_ = start_ + n;
	}

	//---------------------------�޸���������ز���-----------------------------
	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position){
		erase(position, position + 1);
	}
	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last){
		difference_type lenOfTail = end() - last;    //β������������
		difference_type lenOfRemoved = last - first; //Ҫɾ��������
		for(; lenOfTail != 0; --lenOfTail){
			auto temp = last - lenOfRemoved;
			*temp = *(last++);
		}
		return first;
	}
	template <class T, class Alloc>
	template <class InputIterator>
	void vector<T, Alloc>::reallocateAndCopy(iterator position, InputIterator first, InputIterator last){
		difference_type newCapacity = getNewCapacity(last - first);
		T* newStart = dataAllocator::allocate(newCapacity);
		T* newEndOfStorge = newStart + newCapacity;
		T* newFinish = TinySTL::uninitialized_copy(begin(), position, newStart);
		newFinish = TinySTL::uninitialized_copy(first, last, newFinish);
		newFinish = TinySTL::uninitialized_copy(position, end(), newFinish);

		destoryAndDeallocateAll();

		start_ = newStart;
		finish_ = newFinish;
		endOfStorge_ = newEndOfStorge;
	}
	template <class T, class Alloc>
	void vector<T, Alloc>::reallocateAndFillN(iterator position, const size_type& n, const value_type& val){
		difference_type newCapacity = getNewCapacity(n);
		T* newStart = dataAllocator::allocate(newCapacity);
		T* newEndOfStorge = newStart + newCapacity;
		T* newFinish = TinySTL::uninitialized_copy(begin(), position, newStart);
		newFinish = TinySTL::uninitialized_fill_n(newFinish, n, val);
		newFinish = TinySTL::uninitialized_copy(position, end(), newFinish);

		destoryAndDeallocateAll();

		start_ = newStart;
		finish_ = newFinish;
		endOfStorge_ = newEndOfStorge;
	}
	template <class T, class Alloc>
	template <class InputIterator>
	void vector<T, Alloc>::insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type){
		difference_type locationLeft = endOfStorge_ - finish_; //ʣ��洢�ռ�
		difference_type locationNeed = last - first;		   //��Ҫ�洢�ռ�
		if(locationLeft >= locationNeed){
			iterator tmpIter = end() - 1;
			for(;tempIter - position >= 0; --tempIter){
				*(tempIter + locationNeed) = *(tempIter);
			}
			TinySTL::uninitialized_copy(first, last, position);
			finish_ += locationNeed;
		} else{
			reallocateAndCopy(position, first, last);
		}
	}
	template <class T, class Alloc>
	template <class Integer>
	void vector<T, Alloc>::insert_aux(iterator position, Integer n, const value_type& value, std::true_type){
		assert(n != 0);
		difference_type locationLeft = endOfStorge_ - finish_; //ʣ��洢�ռ�
		defference_type locationNeed = n;                      //��Ҫ�洢�ռ�
		if(locationLeft >= locationNeed){
			iterator tempIter = end() - 1;
			for(; tempIter - position >= 0; --tempIter){
				*(tempIter + locationNeed) = *(tempIter);
			}
			TinySTL::uninitialized_fill_n(position, n, value);
			finish_ += locationNeed;
		} else{
			reallocateAndFillN(positon, n, value);	
		}
	}
	template <class T, class Alloc>
	void vector<T, Alloc>::insert(iterator position, const size_type n, const type_value& val){
		insert_aux(position, n, val, typename std::is_integral<size_type>::type());
	}
	template <class T, class Alloc>
	template <class InputIterator>
	void vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last){
		insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
	}
	template <class T, class Alloc>
	vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator position, const value_type& val){
		const iterator index = position - begin();
		insert(position, 1, val);
		return begin() + index;
	}
	template <class T, class Alloc>
	void vector<T, Alloc>::push_back(const value_type& val){
		insert(end(), val);
	}

	//---------------------------�߼��Ƚϲ������-----------------------------
	template <class T, class Alloc>
	bool vector<T, Alloc>::operator==(const vector& v){
		if(size() != v.size()){
			return false;
		} else {
			iterator iter1 = start_;
			iterator iter2 = v.start_;
			for(; iter1 != finish_ && iter2 != v.finish_; ++iter1, ++iter2){
				if(*iter1 != *iter2)
					return false;
			}
			return true;
		}
	}
	template <class T, class Alloc>
	bool vector<T, Alloc>::operator!=(const vector& v){
		return !(*this == v);
	}
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2){
		return v1 == v2;
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2){
		return !(v1 == v2);
	}
}
#endif
