			template <class InputIterator>
			void insert(iterator position, typename enable_if< (is_same<InputIterator, pointer>::value 
				|| is_same<InputIterator, const_pointer>::value || is_same<InputIterator, iterator>::value
				|| is_same<InputIterator, const_iterator>::value), InputIterator>::type first
				, InputIterator last) {
				difference_type offset = position - begin();
				// vector newv(*this);
				// newv.reserve(capacity());
				// std::cout << "_v :" << std::endl;
				// print_vec_inside<vector<T> >(*this);
				// std::cout << "_newv :" << std::endl;
				// print_vec_inside<vector<T> >(newv);
				// newv.insert_meta<InputIterator>(offset, first, last);
				// swap(newv);
				// newv.clear();
				// (void)offset;
				difference_type n = last - first;
				if (n + _n > _capacity * 2)
					_realloc_capacity(_capacity + n);
				if (n + _n > _capacity)
					_realloc_capacity(_capacity * 2);
				// std::cout << "ici" << std::endl;
				for (difference_type i = _n + n - 1; i >= offset + n; i--) {
					if (i < _n)
						_alloc.destroy(&_v[i]);
					_alloc.construct(&_v[i], _v[i - n]);
				}
				// for (difference_type i = offset + n - 1; i >= offset; i--) {
				// 	if (i < _n)
				// 		_alloc.destroy(&_v[i]);
				// 	_alloc.construct(&_v[i], *(last - 1 + (i - offset - n + 1)));
				// }
				for (difference_type i = offset; first != last; i++) {
					// std::cout << "test, _n = " << _n << ", i = " << i << ", *first = " << *first << std::endl;
					if (i < _n) {
						// std::cout << "_v[i] = " << _v[i] << std::endl;
						_alloc.destroy(&_v[i]);
					}
					_alloc.construct(&_v[i], *first);
					first++;
				_n += n;
				}
			}
			
			template <class It>
			void insert_meta(difference_type & offset, It first, It last) {
				// difference_type offset = position - begin();
				// (void)offset;
				difference_type n = last - first;
				if (n + _n > _capacity * 2)
					_realloc_capacity(_capacity + n);
				if (n + _n > _capacity)
					_realloc_capacity(_capacity * 2);
				for (difference_type i = _n + n - 1; i >= offset + n; i--) {
					
					if (i < _n)
						_alloc.destroy(&_v[i]);
					_alloc.construct(&_v[i], _v[i - n]);
				}
				// for (difference_type i = offset + n - 1; i >= offset; i--) {
				// 	if (i < _n)
				// 		_alloc.destroy(&_v[i]);
				// 	_alloc.construct(&_v[i], *(last - 1 + (i - offset - n + 1)));
				// }
				for (difference_type i = offset; first != last; i++) {
					std::cout << "test, _n = " << _n << ", i = " << i << ", *first = " << *first << std::endl;
					if (i < _n) {
						std::cout << "_v[i] = " << _v[i] << std::endl;
						_alloc.destroy(&_v[i]);
					}
					_alloc.construct(&_v[i], *first);
					first++;
					// _n++;
				}
				_n += n;
			}