#ifndef ITERATOR_H
#define ITERATOR_H

namespace TinySTL{

	//五种迭代器类型
	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_iterator_tag: public input_iterator_tag{};
	struct bidirectional_iterator_tag: public forward_iterator_tag{};
	struct random_access_iterator_tag: public bidirectional_iterator_tag{};

	//五种迭代器------------------------------------------------------------------------------------
	template<class T, class Distance>
	struct input_iterator{
		typedef input_iterator_tag  iterator_category;
		typedef T                   value_type;
		typedef Distance            difference_type;
		typedef T*                  pointer;
		typedef T&                  reference;
	};

	struct output_iterator{
		typedef output_iterator_tag  iterator_category;
		typedef void                 value_type;
		typedef void                 difference_type;
		typedef void                 pointer;
		typedef void                 reference;
	};

	template<class T, class Distance>
	struct forward_iterator{
		typedef forward_iterator_tag  iterator_catetory;
		typedef T                     value_type;
		typedef Distance              difference_type;
		typedef T*                    pointer;
		typedef T&                    reference;
	};

	template<class T, class Distance>
	struct bidirectional_iterator{
		typedef bidirectional_iterator_tag  iterator_category;
		typedef T                           value_type;
		typedef Distance                    difference_type;
		typedef T*                          pointer;
		typedef T&                          reference;
	};

	template<class T, class Distance>
	struct random_access_iterator{
		typedef random_access_iterator_tag  iterator_category;
		typedef T                           value_type;
		typedef Distance                    difference_type;
		typedef T*                          pointer;
		typedef T&                          reference;
	};
	
	//新设计的迭代器必须继承自它，就可以保证任何迭代器提供五个内嵌相应型别----------------------------------
	//设计适当的相应型别，是迭代器的责任。设计适当的迭代器，是容器的责任。
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator{
		typedef Category   iterator_category;
		typedef T          value_type;
		typedef Distance   difference_type;
		typedef Pointer    pointer;
		typedef Reference  reference;
	};

	//iterator_traits，迭代器类型萃取------------------------------------------------------------------------
	template<class Iterator>
	struct iterator_traits{
		typedef typename Iterator::iterator_category  iteator_category;
		typedef typename Iterator::value_type         value_type;
		typedef typename Iterator::difference_type    difference_type;
		typedef typename Iterator::pointer            pointer;
		typedef typename Iterator::reference          reference;
	};

	//原生指针偏特化
	template<class T>
	struct iterator_traits<T*>{
		typedef random_access_iterator_tag  iterator_category;
		typedef T                           value_type;
		typedef ptrdiff_t                   difference_type;
		typedef T*                          pointer;
		typedef T&                          reference;
	};

	template<class T>
	struct iterator_traits<const T*>{
		typedef random_access_iterator_tag  iterator_category;
		typedef T                           value_type;
		typedef ptrdiff_t                   difference_type;
		typedef const T*                    pointer;
		typedef const T&                    reference;
	};

	//返回型别的函数-----------------------------------------------------------------------------------------------
	template<class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
		iterator_category(const Iterator& It){
		typedef typename iterator_traits<Iterator>::iterator_category category;
		//category是一个类，此时产生一个暂时对象，如int()产生一个临时对象一样
		return category();
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::value_type
		value_type(const Iterator& It){
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
		difference_type(const Iterator& It){
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}
}

#endif