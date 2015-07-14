#include "VectorTest.h"

namespace TinySTL{
	namespace VectorTest{
		//构造函数
		void testCase1(){
			std::vector<std::string> v3(10);
			TinySTL::vector<std::string> v4(10);
			assert(TinySTL::Test::container_equal(v3, v4));

			std::vector<std::string> v1(10, "sinnera");
			TinySTL::vector<std::string> v2(10, "sinnera");
			assert(TinySTL::Test::container_equal(v1, v2));

			std::array<std::string, 3> arr = { "abc", "def", "ghi" };
			std::vector<std::string> v5(std::begin(arr), std::end(arr));
			TinySTL::vector<std::string> v6(std::begin(arr), std::end(arr));
			assert(TinySTL::Test::container_equal(v5, v6));
		}

		//拷贝构造函数，赋值运算符
		void testCase2(){
			std::vector<int> temp1(10, 0);
			TinySTL::vector<int> temp2(10, 0);

			std::vector<int> v1(temp1);
			TinySTL::vector<int> v2(temp2);
			assert(TinySTL::Test::container_equal(v1, v2));

			std::vector<int> v5 = v1;
			TinySTL::vector<int> v6 = v2;
			assert(TinySTL::Test::container_equal(v5, v6));
		}

		//比较相关
		void testCase3(){
			TinySTL::vector<int> v1, v2;
			for(int i = 0; i < 100; i++){
				v1.push_back(i);
				v2.push_back(i);
			}
			assert(v1 == v2);
			assert(!(v1 != v2));
		}

		//迭代器相关
		void testCase4(){
			TinySTL::vector<int> myvector;
			for (int i = 1; i <= 5; i++)
				myvector.push_back(i);

			int i = 1;
			for (TinySTL::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it, ++i){
				assert(*it == i);
			}

			i = 1;
			for (TinySTL::vector<int>::const_iterator it = myvector.cbegin(); it != myvector.cend(); ++it, ++i){
				assert(*it == i);
			}
		}

		/*void testCase5(){
			TinySTL::vector<int> myvector(5);

			int i = 1;
			for (TinySTL::vector<int>::reverse_iterator it = myvector.rbegin();; it != myvector.rend(); ++it, ++i)
				*it = i;

			i = 5;
			for (TinySTL::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it, --i){
				assert(*it == i);
			}

			i = 1;
			for (TinySTL::vector<int>::reverse_iterator it = myvector.rbegin(); it != myvector.rend(); ++it, ++i){
				assert(*it == i);
			}
		}*/

		//容量相关
		void testCase6(){
			TinySTL::vector<int> vec(11, 0);
			assert(vec.size() == 11);

			vec.resize(5);
			assert(vec.size() == 5);

			vec.resize(20);
			assert(vec.size() == 20);
		}

		void testCase7(){
			TinySTL::vector<int> vec;
			vec.reserve(20);
			assert(vec.capacity() == 20);
		}
	}
}