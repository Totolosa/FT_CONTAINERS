
#include <iostream>
#ifdef MINE
	#include "vector.hpp"
#else
	#include <vector>
	namespace ft = std;
#endif

void test_capacity() {
	std::cout << "test_capacity" << std::endl;
}