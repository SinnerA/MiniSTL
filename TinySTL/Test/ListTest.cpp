#include "ListTest.h"

namespace TinySTL{
	namespace ListTest{
		//构造，拷贝赋值
		void testCase1(){
			std::list<int> l1;
			TinySTL::list<int> l2;
			assert(TinySTL::Test::container_equal(l1, l2));
			
			std::list<int> l3(10, 0);
			TinySTL::list<int> l4(10, 0);
			assert(TinySTL::Test::container_equal(l3, l4));

			int arr[] = {1,2,3,4,5,6,7,8,9,10};
			std::list<int> l5(std::begin(arr), std::end(arr));
			TinySTL::list<int> l6(std::begin(arr), std::end(arr));
			assert(TinySTL::Test::container_equal(l5, l6));

			std::list<int> l7(l5);
			TinySTL::list<int> l8(l6);
			assert(TinySTL::Test::container_equal(l7, l8));

			std::list<int> l9 = l7;
			TinySTL::list<int> l10 = l8;
			assert(TinySTL::Test::container_equal(l9, l10));
		}

		//迭代器

		//访问元素

		//容量
		void testCase2(){
			TinySTL::list<std::string> l1;
			assert(l1.empty());
			assert(l1.size() == 0);

			std::string arr[] = {"1", "2", "3"};
			TinySTL::list<std::string> l2(std::begin(arr), std::end(arr));
			assert(!l2.empty());
			assert(l2.size() == 3);
		}
	}
}