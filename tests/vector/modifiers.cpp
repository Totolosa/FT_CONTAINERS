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

	std::cout << "----------> pop_back <----------" << std::endl;
	v.pop_back();
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
	vector<int>::iterator it2 = v.insert(it0, 100);
	std::cout << "insert it2 = " << *it2 << std::endl;
	print_vec<vector<int> >(v);
	vector<int>::iterator it3 = v.insert(v.begin() + 7, static_cast<size_t>(2), 0);
	std::cout << "insert it3 = " << *it3 << std::endl;
	print_vec<vector<int> >(v);
	vector<int>::iterator it4 = v.insert(v.end(), static_cast<size_t>(20), 666);
	std::cout << "insert it4 = " << *it4 << std::endl;
	print_vec<vector<int> >(v);

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
	it = v.erase(v.begin() + 7, v.begin() + 11);
	std::cout << "erase it = " << *it << std::endl;
	print_vec<vector<int> >(v);
	it = v.erase(v.begin(), v.end());
	std::cout << "erase it = " << *it << std::endl;
	print_vec<vector<int> >(v);
	v.insert(v.begin(), static_cast<size_t>(20), 1);

	std::cout << "----------> swap <----------" << std::endl;
	vector<int> v2;
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	v2.push_back(4);
	v2.push_back(5);
	std::cout << "v :" << std::endl;
	print_vec<vector<int> >(v);
	std::cout << "v2 :" << std::endl;
	print_vec<vector<int> >(v2);
	v.swap(v2);
	std::cout << "v :" << std::endl;
	print_vec<vector<int> >(v);
	std::cout << "v2 :" << std::endl;
	print_vec<vector<int> >(v2);

	std::cout << "----------> clear <----------" << std::endl;
	print_vec<vector<int> >(v);
	v.clear();
	print_vec<vector<int> >(v);
	vector<int> v_empty;
	print_vec<vector<int> >(v_empty);
	v_empty.clear();
	print_vec<vector<int> >(v_empty);

	return 0;
}