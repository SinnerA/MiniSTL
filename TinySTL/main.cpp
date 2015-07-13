#include <iostream>
#include <memory>
#include <string>
#include <vector>
//#include <time.h>

#include "Profiler\Profiler.h"
#include "Allocator.h"
#include "Construct.h"
#include "Vector.h"

using namespace std;
using namespace TinySTL::Profiler;

int main(){
	std::vector<int> vec;
	TinySTL::vector<int> myVec;
	ProfilerInstance::start();
	//int startTime = clock();

	for(int i = 0; i < 10000000; i++){
		//vec.push_back(i);
		myVec.push_back(i);
	}
	//int finishTime = clock();
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
	//cout << finishTime - startTime;
	getchar();
	return 0;
}
//
//#include <iostream>
//#include <memory>
//#include <string>
// 
//#include "Allocator.h"
//#include "Construct.h"
//#include "Vector.h"
//
//using namespace std;
//
//int main(){
//	cout << "Helo World" << endl;
//	
//	int array[10] = {1,2,3,4,5,6,7,8,9,10};
//	TinySTL::vector<int> vec(array, array + 10);
//	for(int i = 0; i < 10; i++) cout << vec[i] << ", ";
//	cout << endl;
//	cout << "size = " << vec.size() << " capacity = " << vec.capacity() << endl;
//	
//	vec.resize(9);
//	for(int i = 0; i < 9; i++) cout << vec[i] << ", ";
//	cout << endl;
//	cout << "size = " << vec.size() << " capacity = " << vec.capacity() << endl;
//
//	vec.resize(20, -1);
//	for(int i = 0; i < 20; i++) cout << vec[i] << ", ";
//	cout << endl;
//	cout << "size = " << vec.size() << " capacity = " << vec.capacity() << endl;
//
//	vec.push_back(0);
//	cout << "size = " << vec.size() << " capacity = " << vec.capacity() << endl;
//
//	getchar();
//	return 0;
//}