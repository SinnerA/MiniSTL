#include <iostream>
#include <memory>

#include "Alloc.h"
#include "Construct.h"

using namespace std;

int main(){
	cout << "Helo World" << endl;

	for(int i = 1; i <= 100000; ++i){
		TinySTL::alloc::allocate(i % 128 * sizeof(int));
	}

	getchar();
	return 0;
}