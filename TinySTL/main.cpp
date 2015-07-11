#include <iostream>
#include <memory>

#include "Alloc.h"
#include "Allocator.h"
#include "Construct.h"

using namespace std;

int main(){
	cout << "Helo World" << endl;

	for(int i = 1; i <= 100000; ++i){
		TinySTL::alloc::allocate(i % 128 * sizeof(int));
		int *p  = TinySTL::allocator<int>::allocate();
		TinySTL::allocator<int>::construct(p, i);
		TinySTL::allocator<int>::destory(p);
		TinySTL::allocator<int>::deallocate(p);
	}

	getchar();
	return 0;
}