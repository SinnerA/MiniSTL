#ifndef TYPE_TRAIT_H
#define TYPE_TRAIT_H

namespace STL{

	struct _true_type{ };
	struct _false_type{ };

	//萃取传入T类型的类型特性-----------------------------------------------------------
	//每一个成员为_true_type，则表示这些类型都可以采用最快速的方式（例如memcpy）来进行拷贝或进行赋值

	//自定义类型，都为_false_type，保守
	template<class T>
	struct _type_traits{
		typedef _false_type has_trivial_default_constructor;
		typedef _false_type has_trivial_copy_constuctor;
		typedef _false_type has_trivial_assignment_operator;
		typedef _false_type has_trivial_destructor;
		typedef _false_type is_POD_type;
	};

	template<>
	struct _type_traits<bool>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<char>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<unsigned char>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<signed char>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<wchar_t>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<short>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<unsigned short>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<int>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<unsigned int>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<long>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<unsigned long>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<long long>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<unsigned long long>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<float>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<double>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<long double>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<char>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	//原生指针的偏特化
	template<class T>
	struct _type_traits<T*>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<class T>
	struct _type_traits<const T*>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<char*>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<unsigned char*>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<signed char*>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<const char*>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<const unsigned char*>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct _type_traits<const signed char*>{
		typedef _true_type has_trivial_default_constructor;
		typedef _true_type has_trivial_copy_constuctor;
		typedef _true_type has_trivial_assignment_operator;
		typedef _true_type has_trivial_destructor;
		typedef _true_type is_POD_type;
	};
}

#endif