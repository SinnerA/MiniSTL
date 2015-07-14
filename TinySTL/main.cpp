#include <iostream>

#include "Algorithm.h"
#include "Profiler\Profiler.h"

#include "Test\VectorTest.h"

using namespace TinySTL::Profiler;

int main(){
	TinySTL::VectorTest::testAllCases();

	getchar();
	return 0;
}