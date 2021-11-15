#include "test_vector.hpp"

int test() {
	vector<int> v;
	print_vec<vector<int> >(v);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	print_vec<vector<int> >(v);

	vector<int> v2(10, 4);
	print_vec<vector<int> >(v2);
	vector<int> v3(20);
	print_vec<vector<int> >(v3);

	vector<int> v4(v2);
	print_vec<vector<int> >(v4);

	return 0;
}