#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include <new>         //ʹ��placement new
#include "TypeTraits.h"

namespace TinySTL{
	//ʹ��placement new����������ʱ��������ڴ棬�����������ڴ��е��ù��캯����������
	//��ptr1��ָ�Ŀռ��ϣ�����һ��ֵΪvalue�Ķ���
	template<class T1, class T2>
	inline void construct(T1 *ptr1, const T2& value){
		new(ptr1) T1(value); 
	}

	//�汾һ������һ��ָ��
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

	//�汾������������������
	//�ж��Ƿ���POD�������ͱ𣩻�ͳC struct�ͱ�
	//POD�ͱ��Ȼ����trivial destructor���Դ�����������
	template<class ForwardIterator>
	inline void destory(ForwardIterator first, ForwardIterator last){
		typedef typename _type_traits<T>::is_POD_type is_POD_type;
		_destory(first, last, is_POD_type);
	}
}

#endif
