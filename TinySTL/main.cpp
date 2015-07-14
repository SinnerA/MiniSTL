#include <iostream>

#include "Algorithm.h"
#include "Profiler\Profiler.h"

#include "Test\VectorTest.h"

using namespace TinySTL::Profiler;

int main(){
	TinySTL::VectorTest::testCase1();
	TinySTL::VectorTest::testCase2();

	getchar();
	return 0;
}