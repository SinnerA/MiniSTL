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
			list<T> *container; //

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


















	}




























}

#endif