#ifndef _UTILITY_H_
#define _UTILITY_H_

namespace TinySTL{
	template <class T>
	void swap(T& a, T& b){
		T temp = a;
		b = a;
		a = temp;
	}
}
#endif