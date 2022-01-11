#include "map.hpp"
// #include "test_map.hpp"
#include <map>
#include <sys/time.h>

class NoLeaksPlease {
	public:
		int			_n;
		std::string	*s;

		NoLeaksPlease() : _n(3) { s = new std::string[_n];};
		NoLeaksPlease(const int & n) : _n(n) { s = new std::string[_n]; };
		NoLeaksPlease(const int & n, const std::string & str) : _n(n) {
			s = new std::string[_n];
			for (int i = 0; i < _n; i++)
				s[i] = str;
		};
		NoLeaksPlease(NoLeaksPlease const & src) : _n(0), s(NULL) { *this = src; }
		~NoLeaksPlease() { delete [] s; };
		int getSize() const { return _n; }
		std::string getString(int index) const { return s[index]; }
		void showstr() const {
			for (int i = 0; i < _n; i++)
				std::cout << "\"" << s[i] << "\"" << std::endl;
		}
		bool operator<(NoLeaksPlease const & rhs) const {
			if (_n < rhs.getSize())
				return true;
			else if (_n > rhs.getSize())
				return false;
			for (int i = 0; i < _n; i++)
				if (s[i] < rhs.getString(i))
					return true;
			return false;
		}
		NoLeaksPlease & operator=(NoLeaksPlease const & cpy) {
			if (s != NULL)
				delete [] s;
			_n = cpy.getSize();
			s = new std::string[_n];
			for (int i = 0; i < cpy.getSize(); i++)
				s[i] = cpy.getString(i);
			return *this;
		}
		friend std::ostream & operator<<(std::ostream & o, NoLeaksPlease const & rhs) {
			// o << "_n = " << rhs.getSize() << ", " ;
			for (int i = 0; i < rhs.getSize(); i++)
				o << "\"" << rhs.getString(i) << "\" " ;
			return o;
		}
};



template <typename C>
void print_map(C &c)
{
	if (c.empty()) {
		std::cout << "Map empty" << std::endl;
		return ;
	}
	for (typename C::iterator it = c.begin(); it != c.end(); ++it)
		std::cout << it->first << "|" << std::flush << it->second << " " << std::flush;
	std::cout << std::endl
		<< "size = " << c.size() << std::endl;
}

template <typename C>
void print_map(const C &c)
{
	if (c.empty()) {
		std::cout << "Map empty" << std::endl;
		return ;
	}
	for (typename C::const_iterator it = c.begin(); it != c.end(); ++it)
		std::cout << it->first << "|" << std::flush << it->second << " " << std::flush;
	std::cout << std::endl
		<< "size = " << c.size() << std::endl;
}


int main() {
	std::__1::chrono::system_clock::time_point start1, end1;
	ft::map<int, NoLeaksPlease> mm;
	std::map<int, NoLeaksPlease> ms;

	// print_map<ft::map<int, NoLeaksPlease> >(mm);
	// ft::map<int, NoLeaksPlease>::iterator test = mm.begin();
	// std::cout << test->first << std::endl;
	

	start1 = std::chrono::system_clock::now();
	// print_map<ft::map<int, NoLeaksPlease> >(mm);
	// mm.insert(ft::make_pair(-2, NoLeaksPlease(2, "-deux")));
	// print_map<ft::map<int, NoLeaksPlease> >(mm);
	// mm.insert(ft::make_pair(-4, NoLeaksPlease(2, "-quatre")));
	// print_map<ft::map<int, NoLeaksPlease> >(mm);

	// mm.insert(ft::make_pair(1, NoLeaksPlease(2, "un")));
	// mm.print_tree();
	// mm.insert(ft::make_pair(3, NoLeaksPlease(2, "trois")));
	// mm.print_tree();
	// mm.insert(ft::make_pair(6, NoLeaksPlease(2, "six")));
	// mm.print_tree();
	// mm.insert(ft::make_pair(7, NoLeaksPlease(2, "sept")));
	// mm.print_tree();
	// mm.insert(ft::make_pair(8, NoLeaksPlease(2, "huit")));
	// mm.print_tree();
	// mm.insert(ft::make_pair(9, NoLeaksPlease(2, "neuf")));
	// mm.print_tree();
	// mm.insert(ft::make_pair(4, NoLeaksPlease(2, "quatre")));
	// mm.print_tree();
	// mm.insert(ft::make_pair(5, NoLeaksPlease(2, "cinq")));

	mm.insert(ft::make_pair(1, NoLeaksPlease(2, "un")));
	mm.print_tree();
	mm.insert(ft::make_pair(3, NoLeaksPlease(2, "trois")));
	mm.print_tree();
	mm.insert(ft::make_pair(7, NoLeaksPlease(2, "sept")));
	mm.print_tree();
	mm.insert(ft::make_pair(2, NoLeaksPlease(2, "deux")));
	mm.print_tree();
	mm.insert(ft::make_pair(0, NoLeaksPlease(2, "zero")));
	mm.print_tree();
	mm.insert(ft::make_pair(8, NoLeaksPlease(2, "huit")));
	mm.print_tree();
	mm.insert(ft::make_pair(9, NoLeaksPlease(2, "neuf")));
	mm.print_tree();
	mm.insert(ft::make_pair(5, NoLeaksPlease(2, "cinq")));
	mm.print_tree();
	mm.insert(ft::make_pair(4, NoLeaksPlease(2, "quatre")));
	mm.print_tree();
	mm.insert(ft::make_pair(6, NoLeaksPlease(2, "six")));
	mm.print_tree();
	mm.insert(ft::make_pair(-1, NoLeaksPlease(2, "-un")));
	mm.print_tree();
	mm.insert(ft::make_pair(-2, NoLeaksPlease(2, "-deux")));
	
	mm.print_tree();
	print_map<ft::map<int, NoLeaksPlease> >(mm);
	end1 = std::chrono::system_clock::now();
	std::cout << "time moi insert = " << (end1 - start1).count() << std::endl;

	start1 = std::chrono::system_clock::now();
	ms.insert(std::make_pair(1, NoLeaksPlease(2, "un")));
	ms.insert(std::make_pair(3, NoLeaksPlease(2, "trois")));
	ms.insert(std::make_pair(7, NoLeaksPlease(2, "sept")));
	ms.insert(std::make_pair(2, NoLeaksPlease(2, "deux")));
	ms.insert(std::make_pair(0, NoLeaksPlease(2, "zero")));
	ms.insert(std::make_pair(8, NoLeaksPlease(2, "huit")));
	ms.insert(std::make_pair(9, NoLeaksPlease(2, "neuf")));
	ms.insert(std::make_pair(5, NoLeaksPlease(2, "cinq")));
	ms.insert(std::make_pair(4, NoLeaksPlease(2, "quatre")));
	ms.insert(std::make_pair(6, NoLeaksPlease(2, "six")));
	ms.insert(std::make_pair(-1, NoLeaksPlease(2, "-un")));
	ms.insert(std::make_pair(-2, NoLeaksPlease(2, "-deux")));
	// print_map<std::map<int, NoLeaksPlease> >(ms);
	end1 = std::chrono::system_clock::now();
	std::cout << "time lib insert = " << (end1 - start1).count() << std::endl;
	std::cout << "TEST" << std::endl;

	// std::cout << "size mm = " << mm.size() << ", size ms = " << ms.size() << std::endl;
	// ft::map<int, NoLeaksPlease>::iterator it = mm.begin();	
	// std::map<int, NoLeaksPlease>::iterator its = ms.begin();
	// std::cout << "(begin == it) = " << (it == mm.begin()) << std::endl;
	// std::cout << "(begin == its) = " << (its == ms.begin()) << std::endl;
	// std::cout <<"it->first = " << it->first << ", it->second = " << it->second << std::endl;
	// std::cout <<"its->first = " << its->first << ", its->second = " << its->second << std::endl;
	// std::cout <<"it->first = " << (++it)->first << ", it->second = " << it->second << std::endl;
	// std::cout <<"its->first = " << (++its)->first << ", its->second = " << its->second << std::endl;
	// std::cout <<"it->first = " << (++it)->first << ", it->second = " << it->second << std::endl;
	// std::cout <<"its->first = " << (++its)->first << ", its->second = " << its->second << std::endl;
	// std::cout <<"it->first = " << (++it)->first << ", it->second = " << it->second << std::endl;
	// std::cout <<"its->first = " << (++its)->first << ", its->second = " << its->second << std::endl;
	// std::cout <<"it->first = " << (++it)->first << ", it->second = " << it->second << std::endl;
	// std::cout <<"its->first = " << (++its)->first << ", its->second = " << its->second << std::endl;


	// std::cout << "(begin == it) = " << (it == mm.begin()) << std::endl;
	// std::cout << "(begin == its) = " << (its == ms.begin()) << std::endl;

	// std::cout << "erase(4) moi = " << mm.erase(4) << std::endl;
	// mm.print_tree();
	// print_map<ft::map<int, NoLeaksPlease> >(mm);
	// std::cout << "erase(4) lib = " << ms.erase(4) << std::endl;
	std::cout << "erase(5) moi = " << mm.erase(5) << std::endl;
	std::cout << "erase(5) lib = " << ms.erase(5) << std::endl;
	mm.print_tree();
	print_map<ft::map<int, NoLeaksPlease> >(mm);
	std::cout << "erase(7) moi = " << mm.erase(7) << std::endl;
	std::cout << "erase(7) lib = " << ms.erase(7) << std::endl;
	mm.print_tree();
	print_map<ft::map<int, NoLeaksPlease> >(mm);
	std::cout << "erase(8) moi = " << mm.erase(8) << std::endl;
	std::cout << "erase(8) lib = " << ms.erase(8) << std::endl;
	mm.print_tree();
	print_map<ft::map<int, NoLeaksPlease> >(mm);
	std::cout << "erase(4) moi = " << mm.erase(4) << std::endl;
	std::cout << "erase(4) lib = " << ms.erase(4) << std::endl;
	mm.print_tree();
	print_map<ft::map<int, NoLeaksPlease> >(mm);
	std::cout << "erase(9) moi = " << mm.erase(9) << std::endl;
	std::cout << "erase(9) lib = " << ms.erase(9) << std::endl;
	mm.print_tree();
	print_map<ft::map<int, NoLeaksPlease> >(mm);
	std::cout << "erase(666) moi = " << mm.erase(666) << std::endl;
	std::cout << "erase(666) lib = " << ms.erase(666) << std::endl;
	mm.print_tree();
	print_map<ft::map<int, NoLeaksPlease> >(mm);
	mm.clear();
	// mm.print_tree();
	print_map<ft::map<int, NoLeaksPlease> >(mm);
	// print_map<ft::map<int, NoLeaksPlease> >(mm);
	// print_map<ft::map<int, NoLeaksPlease> >(mm);
	// print_map<std::map<int, NoLeaksPlease> >(ms);
	// std::cout << "erase(3) moi = " << mm.erase(3) << std::endl;
	// std::cout << "erase(3) lib = " << ms.erase(3) << std::endl;
	// print_map<ft::map<int, NoLeaksPlease> >(mm);
	// print_map<std::map<int, NoLeaksPlease> >(ms);
	// std::cout << "erase(10) moi = " << mm.erase(10) << std::endl;
	// std::cout << "erase(10) lib = " << ms.erase(10) << std::endl;
	// print_map<ft::map<int, NoLeaksPlease> >(mm);
	// print_map<std::map<int, NoLeaksPlease> >(ms);
	// std::cout << "erase(-1) moi = " << mm.erase(-1) << std::endl;
	// std::cout << "erase(-1) lib = " << ms.erase(-1) << std::endl;
	// print_map<ft::map<int, NoLeaksPlease> >(mm);
	// print_map<std::map<int, NoLeaksPlease> >(ms);
	// std::cout << "erase(not in map) moi = " << mm.erase(64894313) << std::endl;
	// std::cout << "erase(not in map) lib = " << ms.erase(64894313) << std::endl;

	// const ft::map<int, NoLeaksPlease> mmc(mm);
	// const std::map<int, NoLeaksPlease> msc(ms);
	// // mm.clear();
	// // ms.clear();
	// // print_map<ft::map<int, NoLeaksPlease> >(mm);
	// // print_map<std::map<int, NoLeaksPlease> >(ms);

	// // {
	// // 	ft::map<int, NoLeaksPlease> mm_tmp;
	// // 	std::map<int, NoLeaksPlease> ms_tmp;
	// // 	mm_tmp.insert(ft::make_pair(100, NoLeaksPlease(2, "cent")));
	// // 	ms_tmp.insert(std::make_pair(100, NoLeaksPlease(2, "cent")));
	// // 	std::cout << "swap moi :" << std::endl;
	// // 	print_map<ft::map<int, NoLeaksPlease> >(mm);
	// // 	print_map<ft::map<int, NoLeaksPlease> >(mm_tmp);
	// // 	mm.swap(mm_tmp);
	// // 	print_map<ft::map<int, NoLeaksPlease> >(mm);
	// // 	print_map<ft::map<int, NoLeaksPlease> >(mm_tmp);
	// // 	std::cout << "swap lib :" << std::endl;
	// // 	print_map<std::map<int, NoLeaksPlease> >(ms);
	// // 	print_map<std::map<int, NoLeaksPlease> >(ms_tmp);
	// // 	ms.swap(ms_tmp);
	// // 	print_map<std::map<int, NoLeaksPlease> >(ms);
	// // 	print_map<std::map<int, NoLeaksPlease> >(ms_tmp);
	// // }
	// {
	// 	std::cout << "moi : find(6) moi = " << (mm.find(6))->first << std::endl;
	// 	std::cout << "lib : find(6) lib = " << (ms.find(6))->first << std::endl;
	// 	std::cout << "moi : find(not in map) moi = " << (mm.find(12347))->first << std::endl;
	// 	if (ms.find(12347) == ms.end())
	// 		std::cout << "lib : find(not in map) = 0" << std::endl;
	// 	else
	// 		std::cout << "lib : find(not in map) = " << (ms.find(12347))->first << std::endl;
	// 	std::cout << "moi : find(6) map const = " << (mmc.find(6))->first << std::endl;
	// 	std::cout << "lib : find(6) map const = " << (msc.find(6))->first << std::endl;
		
	// 	std::cout << "count(6) moi = " << mm.count(6) << std::endl;
	// 	std::cout << "count(6) lib = " << ms.count(6) << std::endl;
	// 	std::cout << "count(not in map) moi = " << mm.count(6549) << std::endl;
	// 	std::cout << "count(not in map) lib = " << ms.count(6549) << std::endl;

	// 	std::cout << "lower_bound(5) moi = " << mm.lower_bound(5)->first << std::endl;
	// 	std::cout << "lower_bound(5) lib = " << ms.lower_bound(5)->first << std::endl;
	// 	std::cout << "lower_bound(5) moi const = " << mmc.lower_bound(5)->first << std::endl;
	// 	std::cout << "lower_bound(5) lib const = " << msc.lower_bound(5)->first << std::endl;

	// 	std::cout << "upper_bound(5) moi = " << mm.upper_bound(5)->first << std::endl;
	// 	std::cout << "upper_bound(5) lib = " << ms.upper_bound(5)->first << std::endl;
	// 	std::cout << "upper_bound(5) moi const = " << mmc.upper_bound(5)->first << std::endl;
	// 	std::cout << "upper_bound(5) lib const = " << msc.upper_bound(5)->first << std::endl;

	// 	std::cout << "equal_range(5) moi = " << mm.equal_range(5).first->first << ", " << mm.equal_range(5).second->first << std::endl;
	// 	std::cout << "equal_range(5) lib = " << ms.equal_range(5).first->first << ", " << ms.equal_range(5).second->first << std::endl;
	// 	std::cout << "equal_range(5) moi const = " << mmc.equal_range(5).first->first << ", " << mmc.equal_range(5).second->first << std::endl;
	// 	std::cout << "equal_range(5) lib const = " << msc.equal_range(5).first->first << ", " << msc.equal_range(5).second->first << std::endl;
	// 	std::cout << "equal_range(3) moi = " << mm.equal_range(3).first->first << ", " << mm.equal_range(3).second->first << std::endl;
	// 	std::cout << "equal_range(3) lib = " << ms.equal_range(3).first->first << ", " << ms.equal_range(3).second->first << std::endl;
	// 	std::cout << "equal_range(3) moi const = " << mmc.equal_range(3).first->first << ", " << mmc.equal_range(3).second->first << std::endl;
	// 	std::cout << "equal_range(3) lib const = " << msc.equal_range(3).first->first << ", " << msc.equal_range(3).second->first << std::endl;
	// // 	// std::cout << "equal_range(4579) moi = " << mm.equal_range(4579).first->first << ", " << mm.equal_range(4579).second->first << std::endl;
	// // 	// std::cout << "equal_range(4579) lib = " << ms.equal_range(4579).first->first << ", " << ms.equal_range(4579).second->first << std::endl;
	// }

	// {
	// 	ft::map<char,int> mymap;
	// 	mymap['x']=1001;
	// 	mymap['y']=2002;
	// 	mymap['z']=3003;
	// 	std::cout << "mymap contains:\n";
	// 	ft::pair<char,int> highest = *(--mymap.end());          // last element
	// 	ft::map<char,int>::iterator it_x = mymap.begin();
	// 	do {
	// 		std::cout << it_x->first << " => " << it_x->second << '\n';
	// 	} while ( mymap.value_comp()(*it_x++, highest) );
	// 	std::map<char,int> libmap;
	// 	libmap['x']=1001;
	// 	libmap['y']=2002;
	// 	libmap['z']=3003;
	// 	std::cout << "libmap contains:\n";
	// 	std::pair<char,int> highest2 = *libmap.rbegin();          // last element
	// 	std::map<char,int>::iterator it_y = libmap.begin();
	// 	do {
	// 		std::cout << it_y->first << " => " << it_y->second << '\n';
	// 	} while ( libmap.value_comp()(*it_y++, highest2) );
	// }

	return 0;
}