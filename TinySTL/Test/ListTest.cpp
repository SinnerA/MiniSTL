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
			/*std::list<int> l1;
			TinySTL::list<int> l2;

			for (int i = 0; i != 10; ++i){
				l1.push_back(i);
				l2.push_back(i);
			}
			auto rit1 = l1.rbegin();
			auto rit2 = l2.rbegin();
			for (; rit1 != l1.rend() && rit2 != l2.rend(); ++rit1, ++rit2){
				assert(*rit1 == *rit2);
			}
			assert(rit1 == l1.rend() && rit2 == l2.rend());*/
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

		void testCase9(){
			std::list<int> l1(10, 0), l3(10, 1);
			TinySTL::list<int> l2(10, 0), l4(10, 1);

			l1.splice(l1.begin(), l3);
			l2.splice(l2.begin(), l4);
			assert(TinySTL::Test::container_equal(l1, l2));

			auto l5 = l1;
			auto l6 = l2;
			l1.splice(l1.end(), l5, l5.begin());
			l2.splice(l2.end(), l6, l6.begin());
			assert(TinySTL::Test::container_equal(l1, l2));

			auto it1 = l1.begin();
			auto it2 = l2.begin();
			for (auto i = 0; i != l1.size() / 2; ++i){
				++it1;
				++it2;
			}
			l1.splice(it1, l5, l5.begin(), l5.end());
			l2.splice(it2, l6, l6.begin(), l6.end());
			assert(TinySTL::Test::container_equal(l1, l2));
		}

		void testCase10(){
			int arr[] = { 17, 89, 7, 14, 89, 0, 1, 4 };
			std::list<int> l1(std::begin(arr), std::end(arr));
			TinySTL::list<int> l2(std::begin(arr), std::end(arr));

			l1.remove(89);
			l2.remove(89);
			assert(TinySTL::Test::container_equal(l1, l2));

			auto func = [](int n){return n % 2 == 0; };
			l1.remove_if(func);
			l2.remove_if(func);
			assert(TinySTL::Test::container_equal(l1, l2));
		}

		void testCase11(){
			int arr[] = { 0, 0, 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 7, 8, 8, 9, 11 };
			std::list<int> l1(std::begin(arr), std::end(arr));
			TinySTL::list<int> l2(std::begin(arr), std::end(arr));

			l1.unique();
			l2.unique();
			assert(TinySTL::Test::container_equal(l1, l2));
		}

		void testCase12(){
			int arr1[] = { 0, 1, 3, 5, 9 }, arr2[] = { 2, 4, 6, 7, 8 };
			std::list<double> first1(std::begin(arr1), std::end(arr1)), second1(std::begin(arr2), std::end(arr2));
			TinySTL::list<double> first2(std::begin(arr1), std::end(arr1)), second2(std::begin(arr2), std::end(arr2));

			first1.merge(second1);
			first2.merge(second2);
			assert(TinySTL::Test::container_equal(first1, first2));
		}

		void testCase13(){
			std::random_device rd;
			std::list<int> l1;
			TinySTL::list<int> l2;
			for (auto i = 0; i != 100; ++i){
				auto ret = rd() % 65536;
				l1.push_back(ret);
				l2.push_back(ret);
			}
			
			l1.sort();
			l2.sort();
			assert(TinySTL::Test::container_equal(l1, l2));

			l1.sort(std::greater<int>());
			l2.sort(std::greater<int>());
			assert(TinySTL::Test::container_equal(l1, l2));
		}

		void testCase14(){
			int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			std::list<int> l1(std::begin(arr), std::end(arr));
			TinySTL::list<int> l2(std::begin(arr), std::end(arr));

			l1.reverse();
			l2.reverse();
			assert(TinySTL::Test::container_equal(l1, l2));
		}

		void testCase15(){
			/*TinySTL::list<int> l1(10, 0), l2(10, 1), l3(10, 0);

			assert(l1 == l3);
			assert(l1 != l2);*/
		}

		void testAllCases(){
			void testCase1();
			void testCase2();
			void testCase3();
			void testCase4();
			void testCase5();
			void testCase6();
			void testCase7();
			void testCase8();
			void testCase9();
			void testCase10();
			void testCase11();
			void testCase12();
			void testCase13();
			void testCase14();
			void testCase15();
		}
	}
}