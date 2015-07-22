#ifndef _LIST_H_
#define _LIST_H_

#include <type_traits>

#include "UninitializedFunctions.h"
#include "Allocator.h"
#include "Iterator.h"
//#include "ReverseIterator.h"

namespace TinySTL{
	template<class T>
	class list;

	namespace Detail{
		//the class of node
		template<class T>
		struct node{
			T data;
			node* prev;
			node* next;
			list<T> *container; //一个指针，表示整个环状双向链表

			node(const T& d, node* p, node* n, list<T>* c):data(d), prev(p), next(n), container(c){}
			bool operator==(const node& n){
				return data == n.data && prev == n.prev && next == n.next && container == n.container;
			}
		};

		//the class of listIterator
		template<class T>
		struct listIterator: public iterator<bidirectional_iterator_tag, T>{
			template<class T>
			friend class list;
		public:
			typedef node<T>* nodePtr;
			nodePtr p;
		public:
			explicit listIterator(nodePtr ptr = nullptr): p(ptr){}
			
			listIterator& operator++();
			listIterator operator++(int);
			listIterator& operator--();
			listIterator operator--(int);
			T& operator*();
			T* operator&();
			
			template<class T>
			friend bool operator==(const listIterator<T>& lhs, const listIterator<T>& rhs);
			template<class T>
			friend bool operator!=(const listIterator<T>& lhs, const listIterator<T>& rhs);
		};
	}//end of namespace

	//the class of list
	template<class T>
	class list{
	private:
		typedef Detail::node<T>* nodePtr;
		typedef allocator<Detail::node<T> > nodeAllocator;
	public:
		typedef T                                   value_type;
		typedef Detail::listIterator<T>             iterator;
		typedef Detail::listIterator<const T>       const_iterator;
		//typedef reverse_iterator_t<iterator>        reverse_iterator;
		typedef T&                                  reference;
		typedef size_t                              size_type;
	private:
		iterator head;
		iterator tail;
	public:
		//构造与拷贝赋值，析构
		list();
		explicit list(size_type n, const value_type& val = value_type());
		template<class InputIterator>
		list(InputIterator first, InputIterator last);
		list(const list&);
		list& operator=(const list&);
		~list();

		//迭代器
		iterator begin() const;
		iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;
		iterator rbegin() const;
		iterator rend() const;

		//修改容器
		void push_back(const value_type& val);
		void push_front(const value_type& val);
		void insert(iterator position, const value_type& val);
		void insert(iterator position, size_type n, const value_type& val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		void erase(iterator position);
		void erase(iterator first, iterator last);

		//访问元素
		

	private:
		nodePtr newNode(const T& val = T());
	};
}
#endif