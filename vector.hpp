#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "includes/containers.hpp"

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class vector {
public:

	//////////////////////////////
	// Iterator subclass
	//////////////////////////////

	template <bool IsConst>
	class vectorIterator {
	public:
		// Member types
		typedef typename		ft::conditional<IsConst, const T, T>::type			value_type;
		typedef					std::ptrdiff_t										difference_type;
		typedef					std::size_t											size_type;
		// -structors
		vectorIterator			(void)												{ _ptr = NULL; }
		~vectorIterator			(void)												{}
		// Const stuff
		template <bool B>		vectorIterator
			(const vectorIterator<B> & x, typename ft::enable_if<!B>::type* = 0)	{ _ptr = x.getPtr(); }

		// Assignment
		vectorIterator &		operator=	(const vectorIterator & x)				{ _ptr = x.getPtr(); return (*this); }
		vectorIterator &		operator+=	(int n)									{ _ptr += n; return (*this); }
		vectorIterator &		operator-=	(int n)									{ _ptr -= n; return (*this); }
		// Comparison
		template <bool B> bool	operator==	(const vectorIterator<B> & x) const		{ return (_ptr == x.getPtr()); }
		template <bool B> bool	operator!=	(const vectorIterator<B> & x) const		{ return (_ptr != x.getPtr()); }
		template <bool B> bool	operator<	(const vectorIterator<B> & x) const		{ return (_ptr < x.getPtr()); }
		template <bool B> bool	operator>	(const vectorIterator<B> & x) const		{ return (_ptr > x.getPtr()); }
		template <bool B> bool	operator<=	(const vectorIterator<B> & x) const		{ return (_ptr <= x.getPtr()); }
		template <bool B> bool	operator>=	(const vectorIterator<B> & x) const		{ return (_ptr >= x.getPtr()); }
		// -crementation
		vectorIterator &		operator++	(void)									{ _ptr++; return (*this); }
		vectorIterator &		operator--	(void)									{ _ptr--; return (*this); }
		vectorIterator			operator++	(int)									{ vectorIterator<IsConst> x(*this); _ptr++; return (x); }
		vectorIterator			operator--	(int)									{ vectorIterator<IsConst> x(*this); _ptr--; return (x); }
		// Operation
		vectorIterator			operator+	(int n) const							{ return (_ptr + n); }
		vectorIterator			operator-	(int n) const							{ return (_ptr - n); }
		difference_type			operator-	(const vectorIterator & x) const		{ return (_ptr - x.getPtr()); }
		// Dereference
		value_type &			operator[]	(size_type n) const						{ return (*(_ptr + n)); }
		value_type &			operator*	(void) const							{ return (*_ptr); }
		value_type *			operator->	(void) const							{ return (_ptr); }
		// Member functions
		value_type *			getPtr		(void) const							{ return (_ptr); }
		// Friend functions
		friend vectorIterator	operator+	(int n, const vectorIterator & x)		{ return (x.getPtr() + n); }
		vectorIterator			(value_type * const ptr)							{ _ptr = ptr; }

	private:
		value_type *			_ptr;
	}; // Iterator

	//////////////////////////////
	// Member types
	//////////////////////////////

	typedef		T												value_type;
	typedef		Alloc											allocator_type;
	typedef		typename allocator_type::reference				reference;
	typedef		typename allocator_type::const_reference		const_reference;
	typedef		typename allocator_type::pointer				pointer;
	typedef		typename allocator_type::const_pointer			const_pointer;
	typedef		vectorIterator<false>							iterator;
	typedef		vectorIterator<true>							const_iterator;
	typedef		ft::reverse_iterator<iterator>					reverse_iterator;
	typedef		ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef		typename vectorIterator<false>::difference_type	difference_type;
	typedef		typename vectorIterator<false>::size_type		size_type;

	//////////////////////////////
	// Constructors
	//////////////////////////////

	//default constructor : Constructs an empty container, with no elements.
	explicit vector (const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;
		_vct = _alloc.allocate(0);
		_size = 0;
		_capacity = 0;
	}

	//fill constructor: Constructs a container with n elements. Each element is a copy of val.
	explicit vector (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;
		_vct = _alloc.allocate(n);
		_size = n;
		_capacity = n;

		for (size_type i = 0 ; i < n ; i++)
			_alloc.construct(_vct + i, val);
	}

	//range constructor: Constructs a container with as many elements as the range [first,last), 
	//		with each element constructed from its corresponding element in that range, in the same order.
	template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(),
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		size_type		n = 0;
		for (InputIterator cpy = first ; cpy != last && n <= this->max_size() ; cpy++)
			n++;

		_alloc = alloc;
		_size = n;
		_capacity = n;
		_vct = _alloc.allocate(n);

		for (size_type i = 0 ; i < n ; i++)
			_alloc.construct(_vct + i, *first++);
	}
	//copy constructor: Constructs a container with a copy of each of the elements in x, in the same order.
	vector (const vector & x)
	{
		_alloc = x._alloc;
		_size = x._size;
		_capacity = x._capacity;
		_vct = _alloc.allocate(_capacity);

		for (size_type i = 0 ; i < _size ; i++)
			_alloc.construct(_vct + i, x[i]);
	}

	//////////////////////////////
	// Destructors
	//////////////////////////////

	~vector (void)
	{
		for (size_type i = 0 ; i < _size ; i++)
			_alloc.destroy(_vct + i);
		_alloc.deallocate(_vct, _capacity);
	}

	//////////////////////////////
	// Assignment operator
	//////////////////////////////

	//Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
	// check if equal else, 
	vector & operator= (const vector & x)
	{
		if (this == &x)
			return (*this);

		for (size_type i = 0 ; i < _size ; i++)
			_alloc.destroy(_vct + i);

		if (x._size > _capacity)
		{
			_alloc.deallocate(_vct, _capacity);
			_capacity = x._size;
			_vct = _alloc.allocate(_capacity);
		}

		_size = x._size;
		for (size_type i = 0 ; i < _size ; i++)
			_alloc.construct(_vct + i, x[i]);

		return (*this);
	}

	//////////////////////////////
	// Iterators
	//////////////////////////////

	iterator begin (void)
	{
		return (iterator(_vct));
	}

	const_iterator begin (void) const
	{
		return (const_iterator(_vct));
	}

	iterator end (void)
	{
		return (iterator(_vct + _size));
	}

	const_iterator end (void) const
	{
		return (const_iterator(_vct + _size));
	}

	//////////////////////////////
	// Reverse iterators
	//////////////////////////////

	reverse_iterator rbegin (void)
	{
		return (reverse_iterator(_vct + _size - 1));
	}

	const_reverse_iterator rbegin (void) const
	{
		return (const_reverse_iterator(_vct + _size - 1));
	}

	reverse_iterator rend (void)
	{
		return (reverse_iterator(_vct - 1));
	}

	const_reverse_iterator rend (void) const
	{
		return (const_reverse_iterator(_vct - 1));
	}

	//////////////////////////////
	// Capacity
	//////////////////////////////

	size_type size (void) const
	{
		return (_size);
	}

	size_type max_size (void) const
	{
		return (_alloc.max_size());
	}

	void resize (size_type n, value_type val = value_type())
	{
		if (n > _size)
		{
			if (n > _capacity)
			{
				if (n > SIZE_OR_CAP_ * 2)
					this->reserve(n);
				else if (SIZE_OR_CAP_ > 0)
					this->reserve(SIZE_OR_CAP_ * 2);
				else
					this->reserve(1);
			}

			for (size_type i = _size ; i < n ; i++)
				_alloc.construct(_vct + i, val);
		}
		else
		{
			for (size_type i = n ; i < _size ; i++)
				_alloc.destroy(_vct + i);
		}

		_size = n;
	}

	size_type capacity (void) const
	{
		return (_capacity);
	}

	bool empty (void) const
	{
		return (_size == 0);
	}

	void reserve (size_type n)
	{
		if (n > _alloc.max_size())
		{
			throw std::length_error("vector::reserve");
		}

		if (n > _capacity)
		{
			T *		new_vct = _alloc.allocate(n);

			for (size_type i = 0 ; i < _size && i < n ; i++)
			{
				_alloc.construct(new_vct + i, _vct[i]);
				_alloc.destroy(_vct + i);
			}
			_alloc.deallocate(_vct, _capacity);

			_capacity = n;
			_vct = new_vct;
		}
	}

	//////////////////////////////
	// Member access
	//////////////////////////////

	reference operator[] (size_type n)
	{
		return (*(_vct + n));
	}

	const_reference operator[] (size_type n) const
	{
		return (*(_vct + n));
	}

	reference at (size_type n)
	{
		if (n >= _size)
		{
			throw std::out_of_range("vector::_M_range_check: __n (which is " + ft::to_string(n) + ") >= this->size() (which is " + ft::to_string(_size) + ")");
		}
		return (_vct[n]);
	}

	const_reference at (size_type n) const
	{
		if (n >= _size)
		{
			throw std::out_of_range("vector::_M_range_check: __n (which is " + ft::to_string(n) + ") >= this->size() (which is " + ft::to_string(_size) + ")");
		}
		return (_vct[n]);
	}

	reference front (void)
	{
		return (_vct[0]);
	}

	const_reference front (void) const
	{
		return (_vct[0]);
	}

	reference back (void)
	{
		return (_vct[_size - 1]);
	}

	const_reference back (void) const
	{
		return (_vct[_size - 1]);
	}

	//////////////////////////////
	// Assignment modifiers
	//////////////////////////////

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last,
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		size_type		n = 0;
		for (InputIterator cpy = first ; cpy != last && n < 1000000 ; cpy++)
			n++;

		if (n > _capacity)
			this->reserve(n);

		for (size_type i = 0 ; i < _size ; i++)
			_alloc.destroy(_vct + i);
		for (size_type i = 0 ; i < n ; i++)
			_alloc.construct(_vct + i, *first++);

		_size = n;
	}

	void assign (size_type n, const value_type & val)
	{
		if (n > _capacity)
			this->reserve(n);

		for (size_type i = 0 ; i < _size ; i++)
			_alloc.destroy(_vct + i);
		for (size_type i = 0 ; i < n ; i++)
			_alloc.construct(_vct + i, val);

		_size = n;
	}

	//////////////////////////////
	// Insertion modifiers
	//////////////////////////////

	iterator insert (iterator position, const value_type & val)
	{
		size_type		off = position - this->begin();
		this->insert(position, 1, val);
		return (iterator(_vct + off));
	}

	void insert (iterator position, size_type n, const value_type & val)
	{
		size_type		off = position - this->begin();

		if (_size + n > _capacity)
		{
			if (_size + n > SIZE_OR_CAP_ * 2)
				this->reserve(_size + n);
			else if (SIZE_OR_CAP_ > 0)
				this->reserve(SIZE_OR_CAP_ * 2);
			else
				this->reserve(1);
		}

		for (size_type i = 0 ; i < n ; i++)
			_alloc.construct(_vct + _size + i, val);
		for (int i = _size - 1 ; i >= 0 && i >= (int)off ; i--)
			_vct[i + n] = _vct[i];
		for (size_type i = off ; i < off + n ; i++)
			_vct[i] = val;
		_size = _size + n;
	}

	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last,
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		size_type		off = position - this->begin();
		size_type		n = 0;
		for (InputIterator cpy = first ; cpy != last && n <= this->max_size() ; cpy++)
			n++;

		if (_size + n > _capacity)
		{
			if (_size + n > SIZE_OR_CAP_ * 2)
				this->reserve(_size + n);
			else if (SIZE_OR_CAP_ > 0)
				this->reserve(SIZE_OR_CAP_ * 2);
			else
				this->reserve(1);
		}

		for (size_type i = 0 ; i < n ; i++)
			_alloc.construct(_vct + _size + i, *first);
		for (int i = _size - 1 ; i >= 0 && i >= (int)off ; i--)
			_vct[i + n] = _vct[i];
		for (size_type i = off ; i < off + n ; i++)
			_vct[i] = *first++;
		_size = _size + n;
	}

	//////////////////////////////
	// Erasure modifiers
	//////////////////////////////

	iterator erase (iterator position)
	{
		for (size_type i = position - this->begin() ; i < _size - 1 ; i++)
			_vct[i] = _vct[i + 1];

		_size--;
		_alloc.destroy(_vct + _size);

		return (position);
	}

	iterator erase (iterator first, iterator last)
	{
		size_type		n = last - first;

		while (n-- > 0)
			this->erase(first);

		return (first);
	}

	//////////////////////////////
	// Common modifiers
	//////////////////////////////

	void push_back (const value_type & val)
	{
		if (_size + 1 > _capacity)
		{
			if (SIZE_OR_CAP_ > 0)
				this->reserve(SIZE_OR_CAP_ * 2);
			else
				this->reserve(1);
		}

		_alloc.construct(_vct + _size, val);
		_size++;
	}

	void pop_back (void)
	{
		if (_size)
		{
			_alloc.destroy(_vct + _size - 1);
			_size--;
		}
	}

	void swap (vector & x)
	{
		ft::swap(_alloc, x._alloc);
		ft::swap(_size, x._size);
		ft::swap(_capacity, x._capacity);
		ft::swap(_vct, x._vct);
	}

	void clear (void)
	{
		for (size_type i = 0 ; i < _size ; i++)
			_alloc.destroy(_vct + i);
		_size = 0;
	}

	//////////////////////////////
	// Allocator
	//////////////////////////////

	allocator_type get_allocator (void) const
	{
		return (allocator_type());
	}

	//////////////////////////////
	// Member variables
	//////////////////////////////

private:
	allocator_type		_alloc;
	size_type			_size;
	size_type			_capacity;
	value_type *		_vct;
}; // Vector

	//////////////////////////////
	// Relational operators
	//////////////////////////////

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs)
	{
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc> & x, vector<T,Alloc> & y)
	{
		x.swap(y);
	}

} // Namespace ft

#endif
