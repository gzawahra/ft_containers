#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
	/////////////////////////////
	// Lexicographical compare //
	/////////////////////////////

	// compare lexicographically ordering like a dictionary ex: ship < sit 
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit < *lit)
				return (false);
			else if (*lit < *rit)
				return (true);
			++lit, ++rit;
		}

		return (rit != rend);
	}

	template <class T>
	bool lexicographical_compare (T & a, T & b)
	{
		return (a < b);
	}

	///////////
	// Equal //
	///////////

	// check equality
	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit != *lit)
				return (false);
			++lit, ++rit;
		}

		return (rit == rend);
	}

	template <class T>
	bool equal (T & a, T & b)
	{
		return (a == b);
	}
}

#endif
