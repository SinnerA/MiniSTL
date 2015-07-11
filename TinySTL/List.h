#ifndef _LIST_H_
#define _LIST_H_

#include <type_traits>

#include "UninitializedFunctions.h"
#include "Allocator.h"
#include "Iterator.h"
#include "ReverseIterator.h"

namespace TinySTL{
	template<class T>
	class list;

	namespace{
		//node
		template<class T>
		struct node{
			T data;
			node* prev;
			node* next;
			list<T> *container; //一个指针，表示整个环状双向链表

			node(const T& data, node* prev, node* next, list<T>* container):
				data(data), prev(prev), next(next), container(container);
			bool operator==(const node& n){
				return data == n.data && prev == n.prev && next == n.next && container == n.container;
			}
		};//end of node class

		template<class T>
		struct listIterator: public bidirectional_iterator<T, ptrdiff_t>{
			template<class T>
			friend class list;
		public:
			typedef node<T>* nodePtr;
			nodePtr p;
		public:
			explicit listIterator(nodePtr ptr = nullptr): p(ptr){}
			
			listIterator& operator++(){
				p = p->next;
				return *this;
			}
			listIterator operator++(int){
				auto res = *this;
				++*this;
				return res;
			}
			listIterator& operator--(){
				p = p->prev;
				return *this;
			}
			listIterator operator--(int){
				auto res = *this;
				--*this;
				return res;
			}

			T& operator*(){ return p->data; }
			T* operator&(){ return &(operator*()); }
			
			template<class T>
			friend bool operator==(const listIterator<T>& lhs, const listIterator<T>& rhs);
			template<class T>
			friend bool operator!=(const listIterator<T>& lhs, const listIterator<T>& rhs);
		};//end of class listIterator
		template<class T>
		bool operator==(const listIterator<T>& lhs, const listIterator<T>& rhs){
			return lhs.p == rhs.p;
		}
		template<class T>
		bool operator!=(const listIterator<T>& lhs, const listIterator<T>& rhs){
			return !(lhs == rhs);
		}
	}//end of namespace

	//the class of list
	template<class T>
	class list{
		template<class T>
		friend struct listIterator;
	private:
		typedef node<T>* nodePtr;
		typedef allocator<node<T> > nodeAllocator;
	public:
		typedef T                             value_type;
		typedef listIterator<T>               iterator;
		typedef reverse_iterator_t<iterator>  reverse_iterator;
		typedef T&                            reference;
		typedef size_t                        size_type;
	private:
		iterator head;
		iterator tail;
	public:
		list(){
			head.p = newNode();//一个空白节点
			tail.p = head.p;
		}
		explicit list(size_type n, const value_type& val = value_type()){
			
		}
	}
}
#endif