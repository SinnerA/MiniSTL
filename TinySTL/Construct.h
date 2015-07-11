#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include <new>         //使用placement new
#include "TypeTraits.h"

namespace TinySTL{
	//使用placement new，创建对象时不会分配内存，而是在已有内存中调用构造函数创建对象
	//在ptr1所指的空间上，创建一个值为value的对象
	template<class T1, class T2>
	inline void construct(T1 *ptr1, const T2& value){
		new(ptr1) T1(value); 
	}

	//版本一：接受一个指针
	template<class T>
	inline void destory(T *ptr){
		ptr->~T();
	}

	template<class ForwardIterator>
	inline void _destory(ForwardIterator first, ForwardIterator last, STL::_true_type){ }

	template<class ForwardIterator>
	inline void _destory(ForwardIterator first, ForwardIterator last, STL::_false_type){
		for(; first != last; ++first){
			destory(&*first);
		}
	}

	//版本二：接受两个迭代器
	//判断是否是POD（标量型别）或传统C struct型别
	//POD型别必然包含trivial destructor（自带析构函数）
	template<class ForwardIterator>
	inline void destory(ForwardIterator first, ForwardIterator last){
		typedef typename _type_traits<T>::is_POD_type is_POD_type;
		_destory(first, last, is_POD_type);
	}
}

#endif
