#include "test_vector.hpp"

int test() {
	vector<int> v;
	std::cout << "----------> push_back <----------" << std::endl;
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

	std::cout << "----------> insert <----------" << std::endl;
	vector<int>::iterator it0 = v.begin() + 3;
	std::cout << "main it = " << *it0 << std::endl;
	vector<int>::iterator it1 = v.insert(it0, 42);
	std::cout << "insert it = " << *it1 << std::endl;
	print_vec<vector<int> >(v);
	v.push_back(6);
	v.push_back(7);
	print_vec<vector<int> >(v);
	// vector<int>::iterator it2 = v.insert(it0, 100);
	// print_vec<vector<int> >(v);
	// std::cout << "insert it2 = " << *it2 << std::endl;
	// vector<int>::iterator it3 = v.insert(v.begin() + 7, static_cast<size_t>(11), 0);
	// std::cout << "insert it3 = " << *it3 << std::endl;
	// print_vec<vector<int> >(v);
	// vector<int>::iterator it4 = v.insert(v.begin() + 20, static_cast<size_t>(3), 666);
	// std::cout << "insert it4 = " << *it4 << std::endl;
	// print_vec<vector<int> >(v);

	std::cout << "----------> erase <----------" << std::endl;
	vector<int>::iterator it = v.erase(v.begin() + 1);
	std::cout << "erase it = " << *it << std::endl;
	print_vec<vector<int> >(v);
	it = v.erase(v.begin());
	std::cout << "erase it = " << *it << std::endl;
	print_vec<vector<int> >(v);
	it = v.erase(v.begin() + v.size() - 1);
	std::cout << "erase it = " << *it << std::endl;
	print_vec<vector<int> >(v);

	
	std::cout << "----------> pop_back <----------" << std::endl;
	v.pop_back();
	print_vec<vector<int> >(v);
	v.pop_back();
	print_vec<vector<int> >(v);
	v.pop_back();
	// print_vec<vector<int> >(v);
	// v.pop_back();
	// print_vec<vector<int> >(v);
	// v.pop_back();
	// print_vec<vector<int> >(v);
	// v.pop_back();
	// print_vec<vector<int> >(v);
	v.push_back(1);
	print_vec<vector<int> >(v);


	return 0;
}