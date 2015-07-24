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

	//辅助函数---------------------------------------------------------------
	template <class T>
	typename list<T>::nodePtr list<T>::newNode(const T& val = T()){
		nodePtr node = nodeAllocator::allocate();
		node->data = val;
		node->container = this;
		node->next = nullptr;
		return node;
	}

	template <class T>
	void list<T>::deleteNode(nodePtr p){
		p->prev = p->next = nullptr;
		nodeAllocator::destory(p);
		nodeAllocator::deallocate(p);
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
	typename list<T>::const_iterator list<T>::changeIteratorToConstIterator(iterator& it)const{
		typedef Detail::node<const T>* nodeP;
		auto ptr = it.p;
		auto temp = (list<const T>* const)this;
		Detail::node<const T> node(ptr->data, (nodeP)(ptr->prev), (nodeP)(ptr->next), temp);
		return const_iterator(&node);
	}

	template <class T>
	void list<T>::insert_aux(iterator pos, size_type n, const value_type& val, std::true_type){
		for(size_type i = n; i > 0; --i){
			insert(pos, val);
		}
	}
	template <class InputIterator>
	void list<T>::insert_aux(iterator pos, InputIterator first, InputIterator last, std::false_type){
		for(--last; last != first; --last){
			pos = insert(pos, *last);
		}
		insert(pos, *last);
	}

	//构造与拷贝赋值，析构----------------------------------------------------
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
		auto temp = (list* const)this;
		return changeIteratorToConstIterator(temp->head);
	}
	template <class T>
	typename list<T>::const_iterator list<T>::end() const{
		auto temp = (list* const)this;
		return changeIteratorToConstIterator(temp->tail);
	}

	/*template <class T>
	typename list<T>::reverse_iterator list<T>::rbegin(){
		return reverse_iterator(tail);
	}
	template <class T>
	typename list<T>::reverse_iterator list<T>::rend(){
		return reverse_iterator(head);
	}*/

	//容量----------------------------------------------------------------------------
	template <class T>
	typename list<T>::size_type list<T>::size() const{
		siez_type length = 0;
		for(iterator it = head; it != tail; ++it){
			++length;
		}
		return length;
	}

	//修改容器-------------------------------------------------------------------------
	template <class T>
	void list<T>::push_front(const value_type& val){
		auto node = newNode(val);
		head.p->prev = node;
		node->next = head.p;
		head.p = node;
	}
	template <class T>
	void list<T>::pop_front(){
		auto oldNode = head.p;
		head.p = head.p->next;
		head.p->prev = nullptr;
		deleteNode(oldNode);
	}
	template <class T>
	void list<T>::push_back(const value_type& val){
		auto node = newNode(val);
		tail.p->next = node;
		node->prev = tail.p;
		tail.p = node;
	}
	template <class T>
	void list<T>::pop_back(){
		auto oldNode = tail.p;
		tail.p = tail.p->prev;
		tail.p->next = nullptr;
		deleteNode(oldNode);
	}

	template <class T>
	void list<T>::insert(iterator pos, const value_type& val){
		if(pos == begin()){
			push_front(val);
			return begin();
		} else if(pos == end()){
			push_back(val);
			return pos;
		}
		auto node = newNode(val);
		auto prev = pos.p->prev;
		prev->next = node;
		node->prev = prev;
		node->next = pos.p;
		pos.p->prev = node;
		return iterator(node);
	}
	
	template <class T>
	void list<T>::insert(iterator pos, size_type n, const value_type& val){
		insert_aux(pos, n, val, typename std::is_integral<value_type>());
	}
	template <class T>
	template <class InputIterator>
	void list<T>::insert(iterator pos, InputIterator first, InputIterator last){
		insert_aux(pos, first, last, typename std::is_integral<InputIterator>());
	}

	template <class T>
	typename list<T>::iterator list<T>::erase(iterator pos){
		if(pos == head){
			pop_front();
			return head;
		}
		auto oldNode = pos.p;
		auto prev = pos.p->prev;
		auto next = pos.p->next;
		prev->next = next;
		next->prev = prev;
		deleteNode(oldNode);
		return iterator(next);
	}
	template <class T>
	typename list<T>::iterator list<T>::erase(iterator first, iterator last){
		for(--last; last != first; --last){
			erase(last);
		}
		return erase(last);
	}

	template <class T>
	void list<T>::clear(){
		erase(begin(), end());
	}

	template <class T>
	void list<T>::swap(list& x){
		TinySTL::swap(head.p, x.head.p);
		TinySTL::swap(tail.p, x.tail.p);
	}

	template <class T>
	void list<T>::splice(iterator pos, list& x){
		this->insert(pos, x.begin(), x.end());
		x.head.p = x.tail.p;
	}
	void splice(iterator pos, list& x, iterator first, iterator last){
		if(first.p == last.p) return;
		if(x.head.p == first.p){
			x.head.p = last.p;
			x.head.p->prev = nullptr;
		} else {
			first.p->prev->next = last.p;
			last.p->prev = first.p->prev;
		}
		auto xTailNode = last.p->prev;
		if(pos.p = head.p){
			first.p->prev = nullptr;
			xTailNode->next = head.p;
			head.p->prev = xTailNode;
			head.p = first.p;
		} else {
			auto posPrev = pos.p->prev;
			posPrev->next = first.p;
			first.p->prev = posPrev;
			xTailNode->next = pos.p;
			pos.p->prev = xTailNode;
		}
	}
	template <class T>
	void list<T>::splice(iterator pos, list& x, iterator i){
		auto next = i;
		this->splice(pos, x, ++next);
	}
}
#endif