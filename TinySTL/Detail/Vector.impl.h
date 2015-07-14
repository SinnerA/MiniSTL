#ifndef _VECTOR_IMPL_H_
#define _VECTOR_IMPL_H_

namespace TinySTL{
	//---------------------------构造，复制，析构相关函数-----------------------------
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
	vector<T, Alloc>::vector(InputIterator begin, InputIterator end){
		//处理指针和数字间的区别的函数
		vector_aux(begin, end, typename std::is_integral<InputIterator>::type());
	}
	template <class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& v){
		if(&rhs != this){
			destoryAndDeallocateAll();
			allocateAndCopy(rhs.start_, rhs.finish_);
		}
		return *this;
	}

	//---------------------------容器容量相关-----------------------------
	template <class T, class Alloc>
	void vector<T, Alloc>::resize(size_type n, value_type val = value_type()){
		if(n < (size_type)size()){
			dataAllocator::destory(start_ + n, finish_);
			finish_ = start_ + n;
		} else if(n > (size_type)size() && n < (size_type)capacity()){
			size_type lengthOfInsert = n - size();
			finish_ = uninitialized_fill_n(finish_, lengthOfInsert, val);
		} else if(n > (size_type)capacity()){
			size_type lengthOfInsert = n - size();
			T* newStart = dataAllocator::allocate(getNewCapacity(lengthOfInsert));
			T* newFinish = TinySTL::uninitialized_copy(begin(), end(), newStart);
			newFinish = TinySTL::uninitialized_fill_n(newFinish, lengthOfInsert, val);

			destoryAndDeallocateAll();
		
			start_ = newStart;
			finish_ = newFinish;
			endOfStorge_ = start_ + n;
		}
	}
	template <class T, class Alloc>
	void vector<T, Alloc>::reserve(size_type n){
		if(n < capacity())
			return;
		T* newStart = dataAllocator::allocate(n);
		T* newFinish = TinySTL::uninitialized_copy(begin(), end(), newStart);

		destoryAndDeallocateAll();

		start_ = newStart;
		finish_ = newFinish;
		endOfStorge_ = start_ + n;
	}
	template <class T, class Alloc>
	void vector<T, Alloc>::shrink_to_fit(){
		dataAllocator::deallocate(finish_, endOfStorge_ - finish_);
		endOfStorge_ = finish_;
	}

	//---------------------------修改容器的相关操作-----------------------------
	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position){
		erase(position, position + 1);
	}
	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last){
		difference_type lenOfTail = end() - last;    //尾部残留对象数
		difference_type lenOfRemoved = last - first; //要删除对象数
		for(; lenOfTail != 0; --lenOfTail){
			auto temp = last - lenOfRemoved;
			*temp = *(last++);
		}
		return first;
	}
	template <class T, class Alloc>
	void vector<T, Alloc>::insert(iterator position, const size_type& n, const value_type& val){
		insert_aux(position, n, val, typename std::is_integral<size_type>::type());
	}
	template <class T, class Alloc>
	template <class InputIterator>
	void vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last){
		insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
	}
	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator position, const value_type& val){
		const auto index = position - begin();
		insert(position, 1, val);
		return begin() + index;
	}
	template <class T, class Alloc>
	void vector<T, Alloc>::push_back(const value_type& val){
		insert(end(), val);
	}
	template <class T, class Alloc>
	void vector<T, Alloc>::pop_back(){
		--finish_;
		dataAllocator::destory(finish_);
	}
	template <class T, class Alloc>
	void vector<T, Alloc>::swap(vector& v){
		if(&v != this){
			std::swap(start_, v.start_);
			std::swap(finish_, v.finish_);
			std::swap(endOfStorge_, v.endOfStorge_);
		}
	}
	template <class T, class Alloc>
	void vector<T, Alloc>::clear(){
		//销毁所有元素，但不回收空间
		dataAllocator::destory(start_, finish_);
		finish_ = start_;
	}

	//---------------------------逻辑比较操作相关-----------------------------
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

	//----------------------------内存分配工具-------------------------------
	template<class T, class Alloc>
	void vector<T, Alloc>::destoryAndDeallocateAll(){
		if(capacity() != 0){
			dataAllocator::destory(start_, finish_);
			dataAllocator::deallocate(start_, endOfStorge_ - start_);
		}
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::allocateAndFillN(const size_type n, const value_type& value){
		start_ = dataAllocator::allocate(n);
		finish_ = endOfStorge_ = start_ + n;
		TinySTL::uninitialized_fill(start_, finish_, value);
	}
	template<class T, class Alloc>
	template <class InputIterator>
	void vector<T, Alloc>::allocateAndCopy(InputIterator first, InputIterator last){
		start_ = dataAllocator::allocate(last - first);
		finish_ = TinySTL::uninitialized_copy(first, last, start_);
		endOfStorge_ = finish_;
	}
	template<class T, class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::vector_aux(InputIterator first, InputIterator last, std::false_type){
		allocateAndCopy(first, last);
	}
	template<class T, class Alloc>
	template<class Integer>
	void vector<T, Alloc>::vector_aux(Integer n, const value_type& value, std::true_type){
		allocateAndFillN(n, value);
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
		difference_type locationLeft = endOfStorge_ - finish_; //剩余存储空间
		difference_type locationNeed = last - first;		   //需要存储空间
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
		difference_type locationLeft = endOfStorge_ - finish_; //剩余存储空间
		difference_type locationNeed = n;                      //需要存储空间
		if(locationLeft >= locationNeed){
			iterator tempIter = end() - 1;
			for(; tempIter - position >= 0; --tempIter){
				*(tempIter + locationNeed) = *(tempIter);
			}
			TinySTL::uninitialized_fill_n(position, n, value);
			finish_ += locationNeed;
		} else{
			reallocateAndFillN(position, n, value);	
		}
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::getNewCapacity(size_type len) const{
		size_type oldCapacity = endOfStorge_ - start_;
		size_type res = std::max(oldCapacity, len);
		size_type newCapacity  = oldCapacity != 0 ? (oldCapacity + res) : len;
		return newCapacity;
	}
}
#endif