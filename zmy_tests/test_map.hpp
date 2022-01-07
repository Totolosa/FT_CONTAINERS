#include <iostream>
#ifdef MINE
#include "map.hpp"
using namespace ft;
#else
#include <map>
using namespace std;
#endif

using std::cout;
using std::endl;

/*
            10
           /  \
          5    21
         / \   / \
        2   8 15  30
       /         /  \
      1        25    42
              / \    / \
            23  27  35  84
             \    \     /
             24   29   43
                  /
                 28
*/
map<int, int> basic()
{
   map<int, int> c;
   c[10] = 10;
   c[5] = 5;
   c[21] = 21;
   c[2] = 2;
   c[8] = 8;
   c[15] = 15;
   c[30] = 30;
   c[1] = 1;
   c[25] = 25;
   c[42] = 42;
   c[23] = 23;
   c[27] = 27;
   c[35] = 35;
   c[84] = 84;
   c[24] = 24;
   c[29] = 29;
   c[28] = 28;
   c[43] = 43;
   return c;
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
		void showstr() const {
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
			// o << "_n = " << rhs.getSize() << ", " ;
			for (int i = 0; i < rhs.getSize(); i++)
				o << "\"" << rhs.getString(i) << "\" " ;
			return o;
		}
};

template <typename C>
void print_map(C &c)
{
  for (typename C::iterator it = c.begin(); it != c.end(); ++it)
    cout << it->first << "|" << std::flush << it->second << " " << std::flush;
  cout << endl
       << "size = " << c.size() << endl;
}

template <typename C>
void print_map(const C &c)
{
  for (typename C::const_iterator it = c.begin(); it != c.end(); ++it)
    cout << it->first << "|" << std::flush << it->second << " " << std::flush;
  cout << endl
       << "size = " << c.size() << endl;
}
