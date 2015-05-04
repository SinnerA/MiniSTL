#include "iostream"

template <class T, class Alloc = alloctor<T>> 
class vector{
private:
	T* start_;       //vector首元素
	T* finish_;      //vector末元素后一个元素
	T* endOfStorge_; //新分配内存中末元素后一个元素

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
	//构造，复制，析构相关函数
	vector()
	        :start_(0), finish_(0), endOfStorge_(0){ }
	explicit vector(const size_type n);
	explicit vector(const size_type n, const value_type& value);
	vector(const vector& v);
	template <class InputIterator>
	vector(InputItertor begin, InputIterator end);
	vector& operator=(const vector &);
	~Vecotor(){ destoryAndDeallocateAll(); }

	//比较相关
	bool operator==(const vector&);
	bool operator!=(const vector&);

	//迭代器相关
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

	//容量相关
	difference_type size() const{ return finish_ - start_; }
	difference_type capacity() const{ return endOfStorge_ - start_; }
	bool empty(){ return start_ == finish_; }
	void resize(size_type n, value_type val = value_type());
	void reverse(size_type n);
	void shrink_to_fit(){
		dataAlloctor::deallocate(finish_, endOfStorge_ - finish_);
		endOfStorge_ = finish_;
	}

	//访问元素相关
	value_type& operator[](const difference_type i){ return *(begin() + i); }
	value_type& front(){ return *(begin()); }
	value_type& back(){ return *(end() - 1); }
	pointer data(){ return start_; }

	//修改容器相关操作
	void clear(){
		//销毁所有元素，但不回收空间
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

	//容器的空间配置器相关
	Alloc get_allocator(){ return dataAllocator; }
private:
	//内存分配工具
	allocator<T> alloc;

	//为底层数组分配空间并初始化
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);
	void uncreate();

	//支持push_back的函数
	void grow();
	void uncheck_append(const T&);
};//end of class vector









template <class T>
vector<T>& vector<T>::operator=(const vector& rhs){
	//判断自我赋值
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
		//相反顺序销毁
		iterator it = avail;
		while(it != data)
			alloc.destory(--it);

		//释放空间
		alloc.deallocate(data, limit - data);
	}
	data = avail = limit = 0;
}

template <class T>
void vector<T>::grow(){
	//扩展大小时，分配2倍内存空间
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

