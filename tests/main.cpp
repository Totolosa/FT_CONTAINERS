#include "vector.hpp"
// #include <vector>

void test();

int main() {
	try {
		test();
		// std::vector<int> v;
		// v.push_back(1);
		// std::cout << "size = " << v.size() << std::endl;
		// std::cout << "capacity = " << v.capacity() << std::endl << std::endl;
		// v.push_back(2);
		// std::cout << "size = " << v.size() << std::endl;
		// std::cout << "capacity = " << v.capacity() << std::endl << std::endl;
		// v.push_back(3);
		// std::cout << "size = " << v.size() << std::endl;
		// std::cout << "capacity = " << v.capacity() << std::endl << std::endl;
		// v.push_back(4);
		// std::cout << "size = " << v.size() << std::endl;
		// std::cout << "capacity = " << v.capacity() << std::endl << std::endl;
		// v.push_back(5);
		// std::cout << "size = " << v.size() << std::endl;
		// std::cout << "capacity = " << v.capacity() << std::endl << std::endl;
	}
	catch (std::out_of_range &e) {
		std::cout << e.what() << std::endl;
	}
	catch (ft::PointerNull &e) {
		std::cout << e.what() << std::endl;
	}
	catch (ft::VectorEmpty &e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::bad_alloc &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}