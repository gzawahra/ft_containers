#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{

template <class T, class Container = vector<T> >
class stack {
public:

	//////////////////////////////
	// Member types
	//////////////////////////////

	typedef		T				value_type;
	typedef		Container		container_type;
	typedef		size_t			size_type;

	//////////////////////////////
	// Member functions
	//////////////////////////////

	explicit stack (const container_type & ctnr = container_type())
	{
		_ctnr = ctnr;
	}

	size_type size (void) const
	{
		return (_ctnr.size());
	}

	bool empty (void) const
	{
		return (_ctnr.empty());
	}

	value_type & top (void)
	{
		return (_ctnr.back());
	}

	const value_type & top (void) const
	{
		return (_ctnr.back());
	}

	void push (const value_type & val)
	{
		_ctnr.push_back(val);
	}

	void pop (void)
	{
		_ctnr.pop_back();
	}

	//////////////////////////////
	// Member variables
	//////////////////////////////

private:
	container_type		_ctnr;

	//////////////////////////////
	// Relational operators
	//////////////////////////////

	friend bool operator== (const stack & lhs, const stack & rhs)
	{
		return (lhs._ctnr == rhs._ctnr);
	}

	friend bool operator<  (const stack & lhs, const stack & rhs)
	{
		return (lhs._ctnr < rhs._ctnr);
	}
}; // Stack

	template <class T, class Container>
	bool operator!= (const stack<T,Container> & lhs, const stack<T,Container> & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container> & lhs, const stack<T,Container> & rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container> & lhs, const stack<T,Container> & rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container> & lhs, const stack<T,Container> & rhs)
	{
		return (!(lhs < rhs));
	}

} // Namespace ft

#endif
