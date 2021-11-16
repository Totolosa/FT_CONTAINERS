#include "test_vector.hpp"

int test() {
	vector<NoLeaksPlease> v;
	// NoLeaksPlease a(3, "test");
	v.insert(v.begin(), NoLeaksPlease(3, "test"));
	// v.push_back(a);
	print_vec<vector<NoLeaksPlease> >(v);


	return 0;
}