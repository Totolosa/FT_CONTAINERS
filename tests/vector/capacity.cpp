
#include "test_vector.hpp"

int test() {
	vector<int> v;
	print_vec<vector<int> >(v);
	v.push_back(1);
	print_vec<vector<int> >(v);
	v.push_back(2);
	print_vec<vector<int> >(v);
	v.push_back(3);
	print_vec<vector<int> >(v);
	v.push_back(4);
	print_vec<vector<int> >(v);
	v.push_back(5);
	print_vec<vector<int> >(v);

	std::cout << "max_size = " << v.max_size() << std::endl << std::endl;

	v.resize(3, 0);
	print_vec<vector<int> >(v);
	v.resize(6);
	print_vec<vector<int> >(v);
	v.resize(12, 9);
	print_vec<vector<int> >(v);

	vector<int> v_empty;
	std::cout << "v.empty = " << v.empty() << std::endl;
	std::cout << "v_empty.empty = " << v_empty.empty() << std::endl << std::endl;
	
	v_empty.reserve(6);
	print_vec<vector<int> >(v_empty);
	v.reserve(3);
	print_vec<vector<int> >(v);
	v.reserve(20);
	print_vec<vector<int> >(v);

	return 0;
}