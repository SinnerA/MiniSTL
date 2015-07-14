#include "VectorTest.h"

namespace TinySTL{
	namespace VectorTest{
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
	}
}