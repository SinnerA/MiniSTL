#include <iostream>
#include <memory>

#include "Alloc.h"
#include "Allocator.h"
#include "Construct.h"
#include "UninitializedFunctions.h"

using namespace std;

int main(){
	cout << "Helo World" << endl;

	/*
	for(int i = 1; i <= 100000; ++i){
		TinySTL::alloc::allocate(i % 128 * sizeof(int));
		int *p  = TinySTL::allocator<int>::allocate();
		TinySTL::allocator<int>::construct(p, i);
		TinySTL::allocator<int>::destory(p);
		TinySTL::allocator<int>::deallocate(p);
	}
	*/
	
	int* p = TinySTL::allocator<int>::allocate(100);
	TinySTL::uninitialized_fill(p, p+100, 1);

	int array[100];
	TinySTL::uninitialized_fill_n(array, 100, 1);
	for(int i = 0; i < 100; i++)
		cout << array[i] << endl;
	

	getchar();
	return 0;
}