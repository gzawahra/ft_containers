#ifndef STRING_HPP
# define STRING_HPP

# include <sstream>

namespace ft
{
	///////////////
	// To string //
	///////////////
	
	// stream string output.
	template <typename T>
	std::string to_string (T n)
	{
		std::ostringstream	ss;
		ss << n;
		return (ss.str());
	}
}

#endif
