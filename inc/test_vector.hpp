#include <iostream>
#ifdef MINE
  #include "vector.hpp"
  using namespace ft;
#else
  #include <vector>
  using namespace std;
#endif

template <typename C>
void print_vec(C & cont) {
	for (typename C::size_type i = 0; i < cont.size(); i++)
		std::cout << cont[i] << "|";
	std::cout << std::endl << "size = " << cont.size() << std::endl;
	std::cout << "capacity = " << cont.capacity() << std::endl << std::endl;
}

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
		void showstr() {
			for (int i = 0; i < _n; i++)
				std::cout << "\"" << s[i] << "\"" << std::endl;
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
			o << "_n = " << rhs.getSize() << ", " ;
			for (int i = 0; i < rhs.getSize(); i++)
				o << "\"" << rhs.getString(i) << "\" " ;
			return o;
		}
};