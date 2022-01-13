#ifndef STACK_HPP
# define STACK_HPP

#include <iostream>
#include <deque>

namespace ft {
	template <typename T, typename Container = std::deque<T> >
	class stack {
		public:
			typedef T											value_type;
			typedef Container									container_type;
			typedef typename container_type::reference			reference;
			typedef typename container_type::const_reference	const_reference;
			typedef typename container_type::size_type			size_type;


			//		--> CONSTRUCTORS/DESTRUCTORS <--
			
			explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}
			~stack() {};


			//		--> MEMBER FUCNTIONS <--

			bool empty() const { return c.empty(); }
			size_type size() const { return c.size(); }
			value_type& top() { return c[size() - 1]; }
			const value_type& top() const { return c[size() - 1]; }
			void push (const value_type& val) { return c.push_back(val); }
			void pop() { return c.pop_back(); }


			//		--> NON MEMBER OPERATORS <--

			template <typename U, typename Cont>
			friend bool operator== (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs) {return lhs.c == rhs.c; }
			template <typename U, typename Cont>
			friend bool operator!= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs) {return lhs.c != rhs.c; }
			template <typename U, typename Cont>
			friend bool operator<  (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs) {return lhs.c < rhs.c; }
			template <typename U, typename Cont>
			friend bool operator<= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs) {return lhs.c <= rhs.c; }
			template <typename U, typename Cont>
			friend bool operator>  (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs) {return lhs.c > rhs.c; }
			template <typename U, typename Cont>
			friend bool operator>= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs) {return lhs.c >= rhs.c; }
			
		protected:
			container_type	c;
	};
}

#endif