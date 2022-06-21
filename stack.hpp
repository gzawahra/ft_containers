#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"


//LIFO stack
//	Stacks are a type of container adaptor, specifically designed to 
//	operate in a LIFO context (last-in first-out), where elements are 
//	inserted and extracted only from one end of the container.
// in this case based on vector container.

namespace ft
{

template <class T, class Container = vector<T> >
class stack {
public:

	//////////////////
	// Member types //
	//////////////////

	typedef		T				value_type; 	//	Type of the elements
	typedef		Container		container_type;	//	Type of the underlying container
	typedef		size_t			size_type;		//	usually the same as size_t

	//////////////////////
	// Member functions //
	//////////////////////

	//	Construct stack
	//	Constructs a stack container adaptor object.

	explicit stack (const container_type & ctnr = container_type())
	{
		std::cout << "construct1" << std::endl;
		c = ctnr;
	}

	//Return size
	//	Returns the number of elements in the stack.
	size_type size (void) const
	{
		std::cout << "size" << std::endl;
		return (c.size());
	}

	//	Test whether container is empty
	//	Returns whether the stack is empty: i.e. whether its size is zero.
	bool empty (void) const
	{
		std::cout << "empty" << std::endl;
		return (c.empty());
	}

	//	Access next element
	//	Returns a reference to the top element in the stack.
	//	Since stacks are last-in first-out containers, the top element 
	//	is the last element inserted into the stack.
	value_type & top (void)
	{
		return (c.back());
	}

	const value_type & top (void) const
	{
		return (c.back());
	}

	//	Inserts a new element at the top of the stack, above its current 
	//	top element. The content of this new element is initialized to a copy of val.
	
	//	This member function effectively calls the member function 
	//	push_back of the underlying container object.
	void push (const value_type & val)
	{
		c.push_back(val);
	}

	//	Removes the element on top of the stack, effectively reducing its size by one.
	//	This member function effectively calls the member function pop_back of 
	//	the underlying container object.
	void pop (void)
	{
		c.pop_back();
	}

	///////////////////////
	// Member variables //
	//////////////////////

protected:
	container_type		c;

	//////////////////////////
	// Relational operators //
	//////////////////////////

	//Each of these operator overloads calls the same operator on the underlying container objects.
	
	friend bool operator== (const stack & lhs, const stack & rhs)
	{
		return (lhs.c == rhs.c);
	}

	friend bool operator<  (const stack & lhs, const stack & rhs)
	{
		return (lhs.c < rhs.c);
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
