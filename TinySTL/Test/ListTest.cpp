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
		void testCase2(){
			
		}

		//访问元素
		void testCase3(){
			std::string arr[] = {"1", "2", "3"};
			TinySTL::list<std::string> l1(std::begin(arr), std::end(arr));
			assert(l1.front() == arr[0]);
			assert(l1.back() == arr[2]);

			l1.front() = "front";
			l1.back() = "back";
			assert(l1.front() == "front");
			assert(l1.back() == "back");
		}

		//容量
		void testCase4(){
			TinySTL::list<std::string> l1;
			assert(l1.empty());
			assert(l1.size() == 0);

			std::string arr[] = {"1", "2", "3"};
			TinySTL::list<std::string> l2(std::begin(arr), std::end(arr));
			assert(!l2.empty());
			assert(l2.size() == 3);
		}

		//修改容器
		void testCase5(){
			std::list<int> l1;
			TinySTL::list<int> l2;
			for(int i = 0; i < 10; i++){
				l1.push_front(i);
				l2.push_front(i);
			}
			assert(TinySTL::Test::container_equal(l1, l2));
			for(int i = 0; i < 10; i++){
				l1.push_back(i);
				l2.push_back(i);
			}
			assert(TinySTL::Test::container_equal(l1, l2));
			for(int i = 0; i < 10; i++){
				l1.pop_front();
				l2.pop_front();
			}
			assert(TinySTL::Test::container_equal(l1, l2));
			for(int i = 0; i < 10; i++){
				l1.pop_back();
				l2.pop_back();
			}
			assert(TinySTL::Test::container_equal(l1, l2));
		}

		void testCase6(){
			std::list<int> l1;
			TinySTL::list<int> l2;
			
			l1.insert(l1.begin(), 1);
			l2.insert(l2.begin(), 1);
			assert(TinySTL::Test::container_equal(l1, l2));

			std::list<int>::iterator it1 = l1.begin();
			TinySTL::list<int>::iterator it2 = l2.begin();
			l1.insert(it1++, 10, 0);
			l2.insert(it2++, 10, 0);
			assert(TinySTL::Test::container_equal(l1, l2));

			int arr[] = {1,2,3,4,5,6,7,8,9,10};
			l1.insert(l1.end(), std::begin(arr), std::end(arr));
			l2.insert(l2.end(), std::begin(arr), std::end(arr));
			assert(TinySTL::Test::container_equal(l1, l2));
		}

		void testCase7(){
			std::list<int> l1;
			TinySTL::list<int> l2;
			for(int i = 0; i < 10; i++){
				l1.push_back(i);
				l2.push_back(i);
			}
			l1.erase(l1.begin());
			l1.erase(--l1.end());
			l2.erase(l2.begin());
			l2.erase(--l2.end());
			assert(TinySTL::Test::container_equal(l1, l2));

			l1.erase(++l1.begin(), --l1.end());
			l2.erase(++l2.begin(), --l2.end());
			assert(TinySTL::Test::container_equal(l1, l2));

			l1.clear();
			l2.clear();
			assert(TinySTL::Test::container_equal(l1, l2));
		}

		void testCase8(){
			TinySTL::list<int> l1, l2;
			l1.push_back(1); l1.push_back(1); l1.push_back(1);
			l2.push_back(2); l2.push_back(2);
			TinySTL::list<int> savedL1 = l1, savedL2 = l2;

			l1.swap(l2);
			assert(TinySTL::Test::container_equal(savedL1, l2));
			assert(TinySTL::Test::container_equal(savedL2, l1));

			savedL1 = l1, savedL2 = l2;
			TinySTL::swap(l1, l2);
			assert(TinySTL::Test::container_equal(savedL1, l2));
			assert(TinySTL::Test::container_equal(savedL2, l1));
		}
	}
}