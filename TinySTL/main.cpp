#include <iostream>
#include <memory>
#include <string>
 
#include "Allocator.h"
#include "Construct.h"
#include "Vector.h"

using namespace std;

int main(){
	cout << "Helo World" << endl;
	
	int array[10] = {1,2,3,4,5,6,7,8,9,10};
	TinySTL::vector<int> vec(array, array + 10);
	for(int i = 0; i < 10; i++)
		cout << vec[i] << ", ";
	cout << endl;

	getchar();
	return 0;
}