#ifndef _STRING_H_
#define _STRING_H_

#include <isotream>
#include <algorithm>
#include <cstddef>
#include <memory>
#include <cstring>
#include <type_traits>

template <class T>
class string{
private:
	char* start_;
	char* finish_;
	char* endOfStorge_;

	typedef TinySTL::allocator<char> dataAllocator;
public:
	
	
};//end of class list

#endif