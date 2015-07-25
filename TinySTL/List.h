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
			T& operator*(){ return p->data; }
			T* operator&(){ return &(operator*()); }
			
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
		iterator tail; //尾节点后一个位置，类似于end()
	public:
		//构造与拷贝赋值，析构
		list();
		explicit list(size_type n, const value_type& val = value_type());
		template<class InputIterator>
		list(InputIterator first, InputIterator last);
		list(const list& l);
		list& operator=(const list& l);
		~list();

		//迭代器
		iterator begin() const;
		iterator end() const;
		const_iterator begin() const;
		const_iterator end() const;
		//reverse_iterator rbegin() const;
		//reverse_iterator rend() const;

		//访问元素
		reference front() const { return head.p->data; }
		reference back() const { return tail.p->prev->data; }

		//容量
		bool empty() const { return head == tail; }
		size_type size() const;

		//修改容器
		void push_front(const value_type& val);
		void pop_front();
		void push_back(const value_type& val);
		void pop_back();

		iterator insert(iterator pos, const value_type& val);
		void insert(iterator pos, size_type n, const value_type& val);
		template <class InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last);
		iterator erase(iterator pos);
		iterator erase(iterator first, iterator last);
		void clear();

		void swap(list& x);
		
		void splice(iterator pos, list& x);
		void splice(iterator pos, list& x, iterator i);
		void splice(iterator pos, list& x, iterator first, iterator last);

		void remove(const value_type& val);
		template <class Predicate>
		void remove_if(Predicate pred);

		void unique();
		template <class BianryPredicate>
		void unique(BianryPredicate binary_pred);

		void merge(list& x);
		template <class Compare>
		void merge(list& x, Compare comp);

		void sort();
		template <class Compare>
		void sort(Compare comp);

		void reverse();
	private:
		//辅助函数
		nodePtr newNode(const T& val = T());
		void deleteNode(nodePtr p);

		void ctorAux(size_type n, const value_type& val, std::true_type);
		template <class InputIterator>
		void ctorAux(InputIterator first, InputIterator last, std::false_type);
		
		const_iterator changeIteratorToConstIterator(iterator& it)const;
		
		void insert_aux(iterator pos, size_type n, const value_type& val, std::true_type);
		template <class InputIterator>
		void insert_aux(iterator pos, InputIterator first, InputIterator last, std::false_type);
	public:
		template <class T>
		friend void swap(list<T>& x, list<T>& y);
		//比较相关
		template <class T>
		friend void operator==(const list<T>& lhs, const list<T>& rhs);
		template <class T>
		friend void operator!=(const list<T>& lhs, const list<T>& rhs);
	};
}

#include "Detail\List.impl.h"
#endif