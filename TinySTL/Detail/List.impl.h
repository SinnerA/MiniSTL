listIterator& operator++(){
				p = p->next;
				return *this;
			}
			listIterator operator++(int){
				nodePtr res = *this;
				++*this;
				return res;
			}
			listIterator& operator--(){
				p = p->prev;
				return *this;
			}
			listIterator operator--(int){
				nodePtr res = *this;
				--*this;
				return res;
			}

			T& operator*(){ return p->data; }
			T* operator&(){ return &(operator*()); }
			
			template<class T>
			friend bool operator==(const listIterator<T>& rhs);
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

		nodePtr newNode(const T& val = T()){
			nodePtr node = nodeAllocator::allocate();
			node->data = val;
			node->container = this;
			node->next = nullptr;
			return node;
		}