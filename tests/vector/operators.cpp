#include "test_vector.hpp"

int test() {
	vector<int> v;
	std::cout << "----------> = <----------" << std::endl;
	print_vec<vector<int> >(v);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	print_vec<vector<int> >(v);

	vector<int> v2 = v;
	print_vec<vector<int> >(v2);
	vector<int> v3;
	v2 = v3;
	print_vec<vector<int> >(v2);

	// std::cout << "----------> <= <----------" << std::endl;


	return 0;
}