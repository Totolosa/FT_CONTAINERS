// #include <iostream>
// #include <string>
// #include <deque>
// #include <iterator>
// #if 1 //CREATE A REAL STL EXAMPLE
// 	#include <map>
	// #include <stack>
// 	#include <vector>
// 	namespace ft = std;
// #else
// 	#include <map.hpp>
// 	#include <stack.hpp>
// 	#include <vector.hpp>
// #endif

// #include <stdlib.h>

// #define MAX_RAM 4294967296
// #define BUFFER_SIZE 4096
// struct Buffer
// {
// 	int idx;
// 	char buff[BUFFER_SIZE];
// };


// #define COUNT (MAX_RAM / (int)sizeof(Buffer))

// template<typename T>
// class MutantStack : public std::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T>& src) { *this = src; }
// 	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}

// 	typedef typename std::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }

// 	int valueint;
// 	long valuelong;
// 	std::string valuestring;

// };

// int main(int argc, char** argv) {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);

// 	ft::vector<std::string> vector_str;
// 	ft::vector<int> vector_int;
// 	ft::stack<int> stack_int;
// 	ft::vector<Buffer> vector_buffer;
// 	ft::stack<Buffer, std::deque<int> > stack_deq_buffer;
// 	ft::map<int, int> map_int;

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	ft::vector<Buffer>().swap(vector_buffer);

// 	try
// 	{
// 		for (int i = 0; i < COUNT; i++)
// 		{
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
// 		}
// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}
	
// 	for (int i = 0; i < COUNT; ++i)
// 	{
// 		map_int.insert(ft::make_pair(rand(), rand()));
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;

// 	{
// 		ft::map<int, int> copy = map_int;
// 	}
// 	MutantStack<char> iterable_stack;
// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 		iterable_stack.push(letter);
// 	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
// 	{
// 		std::cout << *it;
// 	}
// 	std::cout << std::endl;

// 	return (0);
// }





#include "vector.hpp"
#include <vector>
#include <iterator>

int main() {
	try {
		// std::cout << "init" << std::endl;
		std::cout << "==================\n-- VECTOR TESTS --\n==================" << std::endl;
		ft::vector<int> test;
		ft::vector<int>::iterator it;
		ft::vector<int>::iterator ite;
		// ft::vector<const int> test;
		// ft::vector<const int>::const_iterator it;
		// ft::vector<const int>::const_iterator ite;

		std::cout << "size = " << test.size() << ", capacity = " << test.capacity() << std::endl;
		test.push_back(8);
		std::cout << "size = " << test.size() << ", capacity = " << test.capacity() << std::endl;
		test.push_back(2);
		std::cout << "size = " << test.size() << ", capacity = " << test.capacity() << std::endl;
		test.push_back(6);
		std::cout << "size = " << test.size() << ", capacity = " << test.capacity() << std::endl;
		it = test.begin();
		std::cout << "test.begin() = " << *it << std::endl;
		it--;
		std::cout << "test.begin() - 1 = " << *it << std::endl;
		it--;
		std::cout << "test.begin() - 2 = " << *it << std::endl;
		it = test.begin();
		ite = test.end();
		std::cout << "ite = " << *ite << std::endl;
		for (ft::vector<int>::iterator tmp = it; tmp != ite; tmp++)
			std::cout << *tmp << std::endl;
		for (ft::vector<int>::iterator tmp = ite; tmp != it; tmp--)
			std::cout << *tmp << std::endl;
		--ite;
		std::cout << "--ite; *ite = " << --(*ite) << std::endl;
		ft::vector<int>::iterator copy_it(it);
		std::cout << "copy_it = " << *copy_it << std::endl;
		if (it == ite)
			std::cout << "it and ite equals" << std::endl;
		else if (it != ite)
			std::cout << "it and ite not equals" << std::endl;
		it = test.begin() + 1;
		ite = test.end() - 1;
		std::cout << "ite = " << *ite << std::endl;



		std::vector<int> lib;
		lib.push_back(10);
		std::vector<int>::iterator lib_it;
		std::vector<int>::iterator lib_ite;
		// std::vector<int>::iterator lib_it = lib.begin() ;
		std::vector<int>::iterator lib_it2 = lib.begin();
		// lib_it2 = lib_it;
		std::cout << "lib_it2 = " << *lib_it2 << std::endl;
		std::cout << "capacity vector lib start = " << lib.capacity() << std::endl;
		lib.push_back(8);
		std::cout << "capacity vector lib start = " << lib.capacity() << std::endl;
		lib.push_back(5);
		std::cout << "capacity vector lib start = " << lib.capacity() << std::endl;
		lib.push_back(2);
		std::cout << "capacity vector lib start = " << lib.capacity() << std::endl;
		
		lib_it = lib.begin();
		std::cout << "lib_it = " << *lib_it << std::endl;
		std::cout << "*lib_it++ = " << *lib_it++ << "; *lib_it = " << *lib_it << std::endl;
		lib_it = lib.begin();
		std::cout << "lib.begin() = " << *lib_it << std::endl;
		lib_it--;
		std::cout << "lib.begin() - 1 = " << *lib_it << std::endl;
		lib_it--;
		std::cout << "lib.begin() - 2 = " << *lib_it << std::endl;
		lib_it = lib.end();
		std::cout << "lib.end() = " << *lib_it << std::endl;
		lib_it++;
		std::cout << "lib.end() + 1 = " << *lib_it << std::endl;
		lib_it++;
		std::cout << "lib.end() + 2 = " << *lib_it << std::endl;

		lib_it = lib.begin();
		lib_ite = lib.end() - 1;
		std::cout << "lib_ite = " << *lib_ite << std::endl;
		std::cout << (lib_it < lib_ite) << std::endl;

	}
	catch (std::out_of_range &e) {
		std::cout << e.what() << std::endl;
	}
	catch (ft::PointerNull &e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::bad_alloc &e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}