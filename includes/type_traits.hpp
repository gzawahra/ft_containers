#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{
	///////////////
	// Enable If //
	///////////////

	// If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.
	// This metafunction is a convenient way to leverage SFINAE prior to C++20's concepts, in particular for conditionally 
	// removing functions from the candidate set based on type traits, allowing separate function overloads or specializations 
	// based on those different type traits.

	template <bool B, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> { typedef T type; };

	/////////////
	// Is Same //
	/////////////

	// If T and U name the same type (taking into account 
	// const/volatile qualifications), provides the member constant value equal 
	// to true. Otherwise value is false.

    // Commutativity is satisfied, i.e. for any two types T and U, is_same<T, U>::value
	// == true if and only if is_same<U, T>::value == true.
	
	template <class T, class U>
	struct is_same { static const bool value = false; };

	template <class T>
	struct is_same<T, T> { static const bool value = true; };

	/////////////////
	// Conditional //
	/////////////////

	// Provides member typedef type, which is defined as T if B is true at compile time, 
	// or as F if B is false.

	template <bool B, class T = void, class U = void>
	struct conditional {};

	template <class T, class U>
	struct conditional<true, T, U> { typedef T type; };

	template <class T, class U>
	struct conditional<false, T, U> { typedef U type; };
}

#endif
