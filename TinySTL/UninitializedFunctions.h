#ifndef _UNINTIALIZED_FUNCTIONS_H_
#define _UNINTIALIZED_FUNCTIONS_H_

#include "Construct.h"
#include "TypeTraits.h"
#include "Iterator.h"
#include "Algorithm.h"

namespace TinySTL{
	//�ж��Ƿ���POD�ͱ�POD�ͱ��Ȼӵ��trivial ctor/dtor/copy/assignment����
	//��ˣ���POD�ͱ��ȡ����Ч�ʵĳ�ֵ��д����������non-POD��ȡ��հ�ȫ������

	//uninitialized_copy------------------------------------------------------------------------------------------------
	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _true_type);
	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _false_type);

	template<class InputIterator, class ForwardIterator>
	ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result){
		typedef typename _type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type is_POD_type;
		_uninitialized_copy_aux(first, last, result, is_POD_type());
	}
	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _true_type){
		memcpy(result, first, (last - first) * sizeof(*first));
		return result + (last - frist);
	}
	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _false_type){
		for(int i = 0;; first != last; ++first, ++i){
			construct((result + i), *first);
		}
		return (result + i);
	}

	//uninitialized_fill------------------------------------------------------------------------------------------------
	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _true_type);
	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _false_type);
	
	template<class ForwardIterator, class T>
	void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value){
		typedef typename _type_traits<T>::is_POD_type is_POD_type;
		_uninitialized_fill_aux(first, last, value, is_POD_type());
	}
	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _true_type){
		fill(first, last, value); //���ɸ߽׺���ִ��
	}
	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _false_type){
		for(int i = 0; first != last; ++first, ++i){
			construct(first, value);
		}
	}

	//uninitialized_fill_n------------------------------------------------------------------------------------------------
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, _true_type);
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, _false_type);

	template<class ForwardIterator, class Size, class T>
	ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& value){
		typedef typename _type_traits<T>::is_POD_type is_POD_type;
		return _uninitialized_fill_n_aux(first, n, value, is_POD_type());
	}
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, _true_type){
		return fill_n(first, n, value); //���ɸ߽׺���ִ��
	}
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, _false_type){
		for(int i = 0; i < n; ++i){
			construct((T*)(first + i), value);
		}
		return (first + i);
	}
}

#endif