namespace ft {

	struct true_type {
		typedef bool		value_type;
		typedef true_type	type;
		static const value_type value = true;
		operator value_type() { return true; } ;
	};

	struct false_type {
		typedef bool		value_type;
		typedef false_type	type;
		static const value_type value = false;
		operator value_type() { return false; } ;
	};

	template <typename T>
	struct is_integral : false_type {};

	template <>
	struct is_integral<bool> : true_type {};
	template <>
	struct is_integral<char> : true_type {};
	template <>
	struct is_integral<wchar_t> : true_type {};
	template <>
	struct is_integral<short int> : true_type {};
	template <>
	struct is_integral<int> : true_type {};
	template <>
	struct is_integral<long int> : true_type {};
	template <>
	struct is_integral<long long int> : true_type {};
	template <>
	struct is_integral<unsigned char> : true_type {};
	template <>
	struct is_integral<unsigned short int> : true_type {};
	template <>
	struct is_integral<unsigned int> : true_type {};
	template <>
	struct is_integral<unsigned long int> : true_type {};
	template <>
	struct is_integral<unsigned long long int> : true_type {};
}