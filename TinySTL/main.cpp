#include <iostream>

#include "Algorithm.h"
#include "Profiler\Profiler.h"

#include "Test\VectorTest.h"

using namespace TinySTL::Profiler;

int main(){
	TinySTL::VectorTest::testCase1();
	TinySTL::VectorTest::testCase2();
	TinySTL::VectorTest::testCase3();
	TinySTL::VectorTest::testCase4();
	//TinySTL::VectorTest::testCase5();
	TinySTL::VectorTest::testCase6();
	TinySTL::VectorTest::testCase7();

	getchar();
	return 0;
}