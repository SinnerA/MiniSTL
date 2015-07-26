#include <iostream>

#include "Algorithm.h"
#include "Profiler\Profiler.h"

#include "Test\VectorTest.h"
#include "Test\ListTest.h"

using namespace TinySTL::Profiler;

int main(){
	TinySTL::VectorTest::testAllCases();
	TinySTL::ListTest::testAllCases();

	getchar();
	return 0;
}