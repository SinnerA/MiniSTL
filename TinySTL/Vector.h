#include "iostream"

template <class T, class Alloc = alloctor<T>> 
class vector{
private:
	T* start_;       //vector��Ԫ��
	T* finish_;      //vectorĩԪ�غ�һ��Ԫ��
	T* endOfStorge_; //�·����ڴ���ĩԪ�غ�һ��Ԫ��

	typedef Alloc dataAlloctor;
public:
	typedef T                            value_type;
	typedef T*                           iterator;
	typedef const T*                     const_iterator;
	typedef reverse_iterator_t<T*>       reverse_iterator;
	typedef reverse_iterator_t<const T*> const_reverse_iterator;
	typedef iterator                     pointer;
	typedef T&                           reference;
	typedef const T&                     const_reference;
	typedef size_t                       size_type;
	typedef ptrdiff_t                    difference_type;
public:
	//���죬���ƣ�������غ���
	vector()
	        :start_(0), finish_(0), endOfStorge_(0){ }
	explicit vector(const size_type n);
	explicit vector(const size_type n, const value_type& value);
	vector(const vector& v);
	template <class InputIterator>
	vector(InputItertor begin, InputIterator end);
	vector& operator=(const vector &);
	~Vecotor(){ destoryAndDeallocateAll(); }

	//�Ƚ����
	bool operator==(const vector&);
	bool operator!=(const vector&);

	//���������
	iterator begin(){ return start_; }
	const_iterator begin() const{ return start_; }
	const_iterator cbegin() const{ return start_; }
	iterator end() { return finish_; }
	const_iterator end() const{ return finish_; }
	const_iterator cend() const{ return finish_; }
	iterator rbegin(){ return reverse_iterator(finish_); }
	const_iterator crbegin(){ return const_reverse_iterator(finish_); }
	iterator rend(){ return reverse_iterator(start_); }
	const_iterator crend(){ return const_reverse_iterator(start_); }

	//�������
	difference_type size() const{ return finish_ - start_; }
	difference_type capacity() const{ return endOfStorge_ - start_; }
	bool empty(){ return start_ == finish_; }
	void resize(size_type n, value_type val = value_type());
	void reverse(size_type n);
	void shrink_to_fit(){
		dataAlloctor::deallocate(finish_, endOfStorge_ - finish_);
		endOfStorge_ = finish_;
	}

	//����Ԫ�����
	value_type& operator[](const difference_type i){ return *(begin() + i); }
	value_type& front(){ return *(begin()); }
	value_type& back(){ return *(end() - 1); }
	pointer data(){ return start_; }

	//�޸�������ز���
	void clear(){
		//��������Ԫ�أ��������տռ�
		dataAlloctor::destory(start_, finish_);
		finish_ = start_;
	}
	void push_back(const value_type& val);
	void pop_back(){
		--finish_;
		dataAllocator::destory(finish_);
	}
	void swap(vector& v){
		if(&v != this){
			TinySTL::swap(start_, v.start_);
			TinySTL::swap(finish_, v.finish_);
			TinySTL::swap(endOfStorge_, v.endOfStorge_);
		}
	}
	iterator insert(iterator position, const value_type& val);
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last);
	iterator erase(iterator position);
	iterator erase(iterator first, iterator last);

	//�����Ŀռ����������
	Alloc get_allocator(){ return dataAllocator; }
private:
	//�ڴ���乤��
	allocator<T> alloc;

	//Ϊ�ײ��������ռ䲢��ʼ��
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);
	void uncreate();

	//֧��push_back�ĺ���
	void grow();
	void uncheck_append(const T&);
};//end of class vector









template <class T>
vector<T>& vector<T>::operator=(const vector& rhs){
	//�ж����Ҹ�ֵ
	if(&rhs != this){
		uncreate();
		create(rhs.begin(), rhs.end());
	}
	return *this;
}

template <class T>
void vector<T>::create(){
	data = avail = limit = 0;
}

template <class T>
void vector<T>::create(size_type n, const T& val){
	data = alloc.allocate(n);
	limit = avail = data + n;
	uninitialization_fill(data, avail, val);
}

template <class T>
void vector<T>::create(const_iterator i, const_iterator j){
	data = alloc.allocate(j - i);
	uninitialization_copy(i, j, data);
}

template <class T>
void vector<T>::uncreate(){
	if(data){
		//�෴˳������
		iterator it = avail;
		while(it != data)
			alloc.destory(--it);

		//�ͷſռ�
		alloc.deallocate(data, limit - data);
	}
	data = avail = limit = 0;
}

template <class T>
void vector<T>::grow(){
	//��չ��Сʱ������2���ڴ�ռ�
	size_type new_size = max(2*(limit - data), ptrdiff_t(1));
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = alloc.uninitialization_copy(data, avail, new_data);

	uncreate();

	data = new_data;
	avail = new_avail;
	limit = data + new_size;
}

template <class T>
void vector<T>::uncheck_append(const T& val){
	alloc.construct(avail++, val);
}

