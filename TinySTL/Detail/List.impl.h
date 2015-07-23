#ifndef _LIST_IMPL_H_
#define _LIST_IMPL_H_

namespace TinySTL{
	namespace Detail{
		template <class T>
		listIterator<T>& listIterator<T>::operator++(){
			p = p->next;
			return *this;
		}
		template <class T>
		listIterator<T> listIterator<T>::operator++(int){
			nodePtr res = *this;
			++*this;
			return res;
		}
		template <class T>
		listIterator<T>& listIterator<T>::operator--(){
			p = p->prev;
			return *this;
		}
		template <class T>
		listIterator<T> listIterator<T>::operator--(int){
			nodePtr res = *this;
			--*this;
			return res;
		}
		
		template<class T>
		bool operator==(const listIterator<T>& lhs, const listIterator<T>& rhs){
			return lhs.p == rhs.p;
		}
		template<class T>
		bool operator!=(const listIterator<T>& lhs, const listIterator<T>& rhs){
			return !(lhs == rhs);
		}
	}

	//构造与拷贝赋值，析构----------------------------------------------------
	//辅助函数
	template <class T>
	typename list<T>::nodePtr list<T>::newNode(const T& val = T()){
		nodePtr node = nodeAllocator::allocate();
		node->data = val;
		node->container = this;
		node->next = nullptr;
		return node;
	}
	template <class T>
	void list<T>::ctorAux(size_type n, const value_type& val, std::true_type){
		head.p = newNode();
		tail.p = head.p;
		while(n--)
			push_back(val);
	}

	template <class T>
	template <class InputIterator>
	void list<T>::ctorAux(InputIterator first, InputIterator last, std::false_type){
		head.p = newNode();
		tail.p = head.p;
		for( ;first != last; ++first)
			push_back(*head);
	}

	template <class T>
	list<T>::list(){
		head.p = newNode(); //头结点
		tail.p = head.p;
	}
	template <class T>
	list<T>::list(size_type n, const value_type& val = value_type()){
		ctorAux(n, val, std::is_integral<value_type>());
	}
	template<class InputIterator>
	list<T>::list(InputIterator first, InputIterator last){
		ctorAux(first, last, std::is_intergral<InputIterator>());
	}
	template <class T>
	list<T>::list(const list& l){
		head.p = newNode(); //头结点
		tail.p = head.p;
		for(auto node = l.head.p; node != l.tail.p; node = node->next){
			push_back(node->data);
		}
	}

	template <class T>
	list<T>::list& operator=(const list& l){
		if(this != &l){
			list(l).swap(*this);
		}
		return *this;
	}

	template <class T>
	list<T>::~list(){
		for(auto iter = head; iter != tail; iter++){
			nodeAllocator::destory(iter.p);
			nodeAllocator::deallocate(iter.p);
		}
		nodeAllocator::destory(tail.p);
		nodeAllocator::deallocate(tail.p);
	}

	//迭代器---------------------------------------------------------------
	template <class T>
	typename list<T>::iterator list<T>::begin() const{
		return head;
	}
	template <class T>
	typename list<T>::iterator list<T>::end() const{
		return tail;
	}
	template <class T>
	typename list<T>::const_iterator list<T>::begin() const{
		return head;
	}
	template <class T>
	typename list<T>::const_iterator list<T>::end() const{
		return tail;
	}
}
#endif