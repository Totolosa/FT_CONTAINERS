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
#include <iomanip>

class pasmal {
	public : 
		pasmal() {}
		pasmal (std::string str, int nbr) : str(str), nbr(nbr) {}
		~pasmal() {}
		std::string str;
		int			nbr;
};

template <typename It, typename Itc, typename Lit, typename Litc>
void display_iterator(std::string str, It a, Itc b, Lit c, Litc d){
	std::cout << "\033[1m\033[33m" << str << " :\033[0m" << std::endl;
	std::cout << "    |" << std::setw(10) << std::left << "iterator" << "|" << std::setw(15) << std::left << "const_iterator" << "|" << std::endl;
	std::cout << "ME  |" << std::setw(10) << std::left << a << "|" << std::setw(15) << std::left << b << "|" << std::endl;
	std::cout << "LIB |" << std::setw(10) << std::left << c << "|"<< std::setw(15) << std::left << d << "|" << std::endl << std::endl;
}

void test_it_spe1() {
	ft::vector<pasmal> v;
	ft::vector<const pasmal> vc;
	std::vector<pasmal> lv;
	std::vector<const pasmal> lvc;
	v.push_back(pasmal("one", 1));
	v.push_back(pasmal("two", 2));
	v.push_back(pasmal("three", 3));
	v.push_back(pasmal("four", 4));
	v.push_back(pasmal("five", 5));
	vc.push_back(pasmal("one", 1));
	vc.push_back(pasmal("two", 2));
	vc.push_back(pasmal("three", 3));
	vc.push_back(pasmal("four", 4));
	vc.push_back(pasmal("five", 5));
	lv.push_back(pasmal("one", 1));
	lv.push_back(pasmal("two", 2));
	lv.push_back(pasmal("three", 3));
	lv.push_back(pasmal("four", 4));
	lv.push_back(pasmal("five", 5));
	lvc.push_back(pasmal("one", 1));
	lvc.push_back(pasmal("two", 2));
	lvc.push_back(pasmal("three", 3));
	lvc.push_back(pasmal("four", 4));
	lvc.push_back(pasmal("five", 5));
	ft::vector<pasmal>::iterator it1 = v.begin() + 2;
	ft::vector<const pasmal>::const_iterator it_c1 = vc.begin() + 2;
	std::vector<pasmal>::iterator lit1 = lv.begin() + 2;
	std::vector<const pasmal>::const_iterator lit_c1 = lvc.begin() + 2;
	display_iterator("-> :", it1->str, it_c1->str, lit1->str, lit_c1->str);
}

void tests_vector() {
	// std::cout << "init" << std::endl;
	std::cout << "\033[1m\033[32m==================\n-> VECTOR TESTS <-\n==================\033[0m" << std::endl;
	ft::vector<int> myv;
	ft::vector<const int> myv_c;
	// ft::vector<const int> myv_c;
	// ft::vector<int>::iterator it, ite;
	// ft::vector<const int>::iterator it_c, ite_c;
	std::vector<int> lib;
	std::vector<int> lib_c;
	// std::vector<const int> lib_c;
	// std::vector<int>::iterator lit, lite;
	// std::vector<const int>::iterator lit_c, lite_c;

	std::cout << "my vector = myv    iterator = it, ite,   const_iterator = it_c, ite_c" << std::endl;
	std::cout << "std::vector = lib  iterator = lit, lite  const_iterator = lit_c, lite_c" << std::endl;

	std::cout << "\033[1m\033[4m\033[34m\n* Methods *\n\033[0m" << std::endl;

	std::cout << "\033[1m\n-> push_back, size, capacity\n\033[0m" << std::endl;
	
	std::cout << "Moi : size = " << myv.size() << ", capacity = " << myv.capacity() << std::endl;
	std::cout << "Lib : size = " << lib.size() << ", capacity = " << lib.capacity() << std::endl << std::endl;
	myv.push_back(1);
	myv_c.push_back(1);
	lib.push_back(1);
	lib_c.push_back(1);
	std::cout << "Moi : size = " << myv.size() << ", capacity = " << myv.capacity() << std::endl;
	std::cout << "Lib : size = " << lib.size() << ", capacity = " << lib.capacity() << std::endl << std::endl;
	myv.push_back(2);
	myv_c.push_back(2);
	lib.push_back(2);
	lib_c.push_back(2);
	std::cout << "Moi : size = " << myv.size() << ", capacity = " << myv.capacity() << std::endl;
	std::cout << "Lib : size = " << lib.size() << ", capacity = " << lib.capacity() << std::endl << std::endl;
	myv.push_back(3);
	myv_c.push_back(3);
	lib.push_back(3);
	lib_c.push_back(3);
	std::cout << "Moi : size = " << myv.size() << ", capacity = " << myv.capacity() << std::endl;
	std::cout << "Lib : size = " << lib.size() << ", capacity = " << lib.capacity() << std::endl << std::endl;
	myv.push_back(4);
	myv_c.push_back(4);
	lib.push_back(4);
	lib_c.push_back(4);
	std::cout << "Moi : size = " << myv.size() << ", capacity = " << myv.capacity() << std::endl;
	std::cout << "Lib : size = " << lib.size() << ", capacity = " << lib.capacity() << std::endl << std::endl;
	
	
	myv.push_back(5);
	myv_c.push_back(5);
	lib.push_back(5);
	lib_c.push_back(5);
	std::cout << "Moi : size = " << myv.size() << ", capacity = " << myv.capacity() << std::endl;
	std::cout << "Lib : size = " << lib.size() << ", capacity = " << lib.capacity() << std::endl << std::endl;
	ft::vector<int> test_empty ;
	ft::vector<int> test_copy = test_empty;
	std::vector<int> test_emptyl ;
	std::vector<int> test_copyl = test_emptyl;
	for (size_t i = 0; i != test_copy.size(); i++)
		std::cout << "me :  value = " << test_copy[i] << ", size = " << test_copy.size() << ", capacity = " << test_copy.capacity() << std::endl;
	for (size_t i = 0; i != test_copyl.size(); i++)
		std::cout << "lib : value = " << test_copyl[i] << ", size = " << test_copyl.size() << ", capacity = " << test_copyl.capacity() << std::endl;
	test_copy = myv;
	test_copyl = lib;
	for (size_t i = 0; i != test_copy.size(); i++)
		std::cout << "me :  value = " << test_copy[i] << ", size = " << test_copy.size() << ", capacity = " << test_copy.capacity() << std::endl;
	for (size_t i = 0; i != test_copyl.size(); i++)
		std::cout << "lib : value = " << test_copyl[i] << ", size = " << test_copyl.size() << ", capacity = " << test_copyl.capacity() << std::endl;
	test_empty.push_back(10);
	test_empty.push_back(11);
	test_empty.push_back(12);
	test_emptyl.push_back(10);
	test_emptyl.push_back(11);
	test_emptyl.push_back(12);
	test_copy = test_empty;
	test_copyl = test_emptyl;
	for (size_t i = 0; i != test_copy.size(); i++)
		std::cout << "me :  value = " << test_copy[i] << ", size = " << test_copy.size() << ", capacity = " << test_copy.capacity() << std::endl;
	for (size_t i = 0; i != test_copyl.size(); i++)
		std::cout << "lib : value = " << test_copyl[i] << ", size = " << test_copyl.size() << ", capacity = " << test_copyl.capacity() << std::endl;


	// std::cout << "\033[1m\033[4m\033[34m\n* Vector Iterators *\n\033[0m" << std::endl;
	// std::cout << "ME  --> iterator = it (begin), ite (end)    const_iterator = it_c (begin), ite_c (end)" << std::endl;
	// std::cout << "LIB --> iterator = lit (begin), lite (end)  const_iterator = lit_c (begin), lite_c (end)" << std::endl;
	// ft::vector<int>::iterator it = myv.begin() + 0;
	// ft::vector<int>::iterator ite = myv.end();
	// ft::vector<const int>::const_iterator it_c = myv_c.begin() + 0;
	// ft::vector<const int>::const_iterator ite_c = myv_c.end();
	// std::vector<int>::iterator lit = lib.begin() + 0;
	// std::vector<int>::iterator lite = lib.end();
	// std::vector<const int>::const_iterator lit_c = lib_c.begin() + 0;
	// std::vector<const int>::const_iterator lite_c = lib_c.end();
	// std::cout << "\033[1m\n-> Operators\n\033[0m" << std::endl;

	// display_iterator("*", *it, *it_c, *lit, *lit_c);
	// // test_it_spe1();
	// it++;
	// it_c++;
	// lit++;
	// lit_c++;
	// display_iterator("it++", *it, *it_c, *lit, *lit_c);
	// ++it;
	// ++it_c;
	// ++lit;
	// ++lit_c;
	// display_iterator("++it", *it, *it_c, *lit, *lit_c);
	// it--;
	// it_c--;
	// lit--;
	// lit_c--;
	// display_iterator("it--", *it, *it_c, *lit, *lit_c);
	// --it;
	// --it_c;
	// --lit;
	// --lit_c;
	// display_iterator("--it", *it, *it_c, *lit, *lit_c);
	// display_iterator("it + 3", *(it + 3), *(it_c + 3), *(lit + 3), *(lit_c + 3));
	// display_iterator("it += 2", *(it += 2), *(it_c += 2), *(lit += 2), *(lit_c += 2));
	// display_iterator("it - 1", *(it - 1), *(it_c - 1), *(lit - 1), *(lit_c - 1));
	// display_iterator("it -= 2", *(it -= 2), *(it_c -= 2), *(lit -= 2), *(lit_c -= 2));
	// display_iterator("it - ite", it - ite, it_c - ite_c, lit - lite, lit_c - lite_c);
	// ft::vector<int>::iterator it1(ite  - 1);
	// ft::vector<const int>::const_iterator it2(ite_c - 1);
	// std::vector<int>::iterator it3(lite - 1);
	// std::vector<const int>::const_iterator it4(lite_c - 1);
	// display_iterator("it = ite", *it1, *it2, *it3, *it4);
	// display_iterator("(it == ite)", (it == ite), (it_c == ite_c), (lit == lite), (lit_c == lite_c));
	// display_iterator("(it != ite)", (it != ite), (it_c != ite_c), (lit != lite), (lit_c != lite_c));
	// display_iterator("(it >= ite)", (it >= ite), (it_c >= ite_c), (lit >= lite), (lit_c >= lite_c));
	// display_iterator("(it > ite)", (it > ite), (it_c > ite_c), (lit > lite), (lit_c > lite_c));
	// display_iterator("(it <= ite)", (it <= ite), (it_c <= ite_c), (lit <= lite), (lit_c <= lite_c));
	// display_iterator("(it < ite)", (it < ite), (it_c < ite_c), (lit < lite), (lit_c < lite_c));





	

}



int main() {
	try {
		tests_vector();

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