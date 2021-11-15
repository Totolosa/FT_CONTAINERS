#include "test_vector.hpp"

int test() {
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	print_vec<vector<int> >(v);

	vector<int>::iterator it = v.begin();
	std::cout << *it << std::endl;
	std::cout << it[3] << std::endl;
	// std::cout << it[-2] << std::endl << std::endl;
	
	return 0;
}