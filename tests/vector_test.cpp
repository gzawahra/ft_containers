# include <vector>
# include <fstream>
# include <cstring>
# include <iostream>

# include "../vector.hpp"

// Linux Colors
# define RESET "\e[0m"
# define BOLD "\e[1m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define BLUE "\e[34m"
# define PINK "\e[35m"

template <class T>
void checkVectorsDiff(std::vector<T>& stl_vector, ft::vector<T>& ft_vector)
{


	if (stl_vector.size() == ft_vector.size())
		std::cout << GREEN << std::endl << "=> size() [OK]" << std::endl;
	else
		std::cout << RED << "size() [ERROR]" << std::endl;

	std::cout << "[STL] Size = " << stl_vector.size() << std::endl;
	std::cout << "[FT]  Size = " << ft_vector.size() << std::endl;

	if (stl_vector.max_size() == ft_vector.max_size())
		std::cout << GREEN << std::endl << "=> max_size() [OK]" << std::endl;
	else
		std::cout << RED << "max_size() [ERROR]" << std::endl;
	std::cout << "[STL] Max Size = " << stl_vector.max_size() << std::endl;
	std::cout << "[FT]  Max Size = " << ft_vector.max_size() << std::endl;

	if (stl_vector.capacity() == ft_vector.capacity())
		std::cout << GREEN << std::endl << "=> capacity() [OK]" << std::endl;
	else
		std::cout << RED << "capacity() [ERROR]" << std::endl;
	std::cout << "[STL] Max Size = " << stl_vector.capacity() << std::endl;
	std::cout << "[FT]  Max Size = " << ft_vector.capacity() << std::endl;

	if (stl_vector.empty() == ft_vector.empty())
		std::cout << GREEN << std::endl << "=> empty() [OK]" << std::endl;
	else
		std::cout << RED << "empty() [ERROR]" << std::endl;
	std::cout << "[STL] Empty = " << stl_vector.empty() << std::endl;
	std::cout << "[FT]  Empty = " << ft_vector.empty() << std::endl << std::endl;
	
	std::cout << RESET << "[STL] Content = [";
	typename std::vector<T>::const_iterator stl_it;
	for (stl_it = stl_vector.begin(); stl_it != stl_vector.end(); stl_it++)
	{
		std::cout << *stl_it;
		if (stl_it + 1 != stl_vector.end())
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;
	std::cout << "[FT]  Content = [";
	typename ft::vector<T>::const_iterator ft_it;
	for (ft_it = ft_vector.begin(); ft_it != ft_vector.end(); ft_it++)
	{
		std::cout << *ft_it;
		if (ft_it + 1 != ft_vector.end())
			std::cout << ", ";
	}
	std::cout << "]" << std::endl << std::endl;
}

void vector_test()
{
	std::cout << BOLD << "VECTOR TESTS: " << RESET << std::endl;

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Default constructor: " << RESET << std::endl;
	std::vector<int> stl_vector_int;
	ft::vector<int> ft_vector_int;
	checkVectorsDiff(stl_vector_int, ft_vector_int);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Default constructor pointer: " << RESET << std::endl;
	std::vector<int> *stl_vector_int_p = new std::vector<int>;
	ft::vector<int> *ft_vector_int_p = new ft::vector<int>;
	checkVectorsDiff(*stl_vector_int_p, *ft_vector_int_p);
	delete stl_vector_int_p;
	delete ft_vector_int_p;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Fill constructor: " << RESET << std::endl;
	std::vector<int> stl_vector_fill(0);
	ft::vector<int> ft_vector_fill(0);
	checkVectorsDiff(stl_vector_fill, ft_vector_fill);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Fill constructor sized: " << RESET << std::endl;
	std::vector<int> stl_vector_fill_sized(42);
	ft::vector<int> ft_vector_fill_sized(42);
	checkVectorsDiff(stl_vector_fill_sized, ft_vector_fill_sized);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Fill constructor sized + value: " << RESET << std::endl;
	std::vector<int> stl_vector_fill_sizedv(42, 42);
	ft::vector<int> ft_vector_fill_sizedv(42, 42);
	checkVectorsDiff(stl_vector_fill_sizedv, ft_vector_fill_sizedv);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Range constructor: " << RESET << std::endl;
	int range_array[] = {42, 21, 123456, 0, 4, 13};
	std::vector<int>::iterator stl_iterator(&(range_array[0]));
	ft::vector<int>::iterator ft_iterator(&(range_array[0]));
	std::vector<int> stl_vector_range(stl_iterator, stl_iterator + 6);
	ft::vector<int> ft_vector_range(ft_iterator, ft_iterator + 6);
	checkVectorsDiff(stl_vector_range, ft_vector_range);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Copy constructor: " << RESET << std::endl;
	std::vector<int> stl_vector_copy(stl_vector_range);
	ft::vector<int> ft_vector_copy(ft_vector_range);
	checkVectorsDiff(stl_vector_copy, ft_vector_copy);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Assign constructor: " << RESET << std::endl;
	std::vector<int> stl_vector_assign = stl_vector_range;
	ft::vector<int> ft_vector_assign = ft_vector_range;
	checkVectorsDiff(stl_vector_assign, ft_vector_assign);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator begin(): " << RESET << std::endl;
	int begin_stl = *(stl_vector_range.begin());
	int begin_ft = *(ft_vector_range.begin());
	if (begin_stl == begin_ft)
		std::cout << GREEN << std::endl << "=> begin() [OK]" << std::endl;
	else
		std::cout << RED << "=> begin() [ERROR]" << std::endl;
	std::cout << "[STL] begin() = " << begin_stl << std::endl;
	std::cout << "[FT]  begin() = " << begin_ft  << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator begin(): " << RESET << std::endl;
	std::vector<int>::const_iterator stl_const_it = stl_vector_range.begin();
	ft::vector<int>::const_iterator ft_const_it = ft_vector_range.begin();
	const int const_begin_stl = *(stl_const_it);
	const int const_begin_ft = *(ft_const_it);
	if (const_begin_stl == const_begin_ft)
		std::cout << GREEN << std::endl << "=> const begin() [OK]" << std::endl;
	else
		std::cout << RED << "=> const begin() [ERROR]" << std::endl;
	std::cout << "[STL] begin() = " << const_begin_stl << std::endl;
	std::cout << "[FT]  begin() = " << const_begin_ft << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator end(): " << RESET << std::endl;
	int end_stl = *(stl_vector_range.end() - 1);
	int end_ft = *(ft_vector_range.end() - 1);
	if (end_stl == end_ft)
		std::cout << GREEN << std::endl << "=> end() [OK]" << std::endl;
	else
		std::cout << RED << "=> end() [ERROR]" << std::endl;
	std::cout << "[STL] end() = " << end_stl << std::endl;
	std::cout << "[FT]  end() = " << end_ft << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator end(): " << RESET << std::endl;
	std::vector<int>::const_iterator stl_const_end = stl_vector_range.end() - 1;
	ft::vector<int>::const_iterator ft_const_end = ft_vector_range.end() - 1;
	const int const_end_stl = *(stl_const_end);
	const int const_end_ft = *(ft_const_end);
	if (const_end_stl == const_end_ft)
		std::cout << GREEN << std::endl << "=> const end() [OK]" << std::endl;
	else
		std::cout << RED << "=> const end() [ERROR]" << std::endl;
	std::cout << "[STL] end() = " << const_end_stl << std::endl;
	std::cout << "[FT]  end() = " << const_end_ft << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator rbegin(): " << RESET << std::endl;
	int rbegin_stl = *(stl_vector_range.rbegin());
	int rbegin_ft = *(ft_vector_range.rbegin());
	if (rbegin_stl == rbegin_ft)
		std::cout << GREEN << std::endl << "=> rbegin() [OK]" << std::endl;
	else
		std::cout << RED << "=> rbegin() [ERROR]" << std::endl;
	std::cout << "[STL] rbegin() = " << rbegin_stl << std::endl;
	std::cout << "[FT]  rbegin() = " << rbegin_ft << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator rbegin(): " << RESET << std::endl;
	std::vector<int>::const_reverse_iterator stl_const_rbegin = stl_vector_range.rbegin();
	ft::vector<int>::const_reverse_iterator ft_const_rbegin = ft_vector_range.rbegin();
	const int const_rbegin_stl = *(stl_const_rbegin);
	const int const_rbegin_ft = *(ft_const_rbegin);
	if (const_rbegin_stl == const_rbegin_ft)
		std::cout << GREEN << std::endl << "=> const rbegin() [OK]" << std::endl;
	else
		std::cout << RED << "=> const rbegin() [ERROR]" << std::endl;
	std::cout << "[STL] rbegin() = " << const_rbegin_stl << std::endl;
	std::cout << "[FT]  rbegin() = " << const_rbegin_ft << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator rend(): " << RESET << std::endl;
	int rend_stl = *(stl_vector_range.rend() - 1);
	int rend_ft = *(ft_vector_range.rend() - 1);
	if (rend_stl == rend_ft)
		std::cout << GREEN << std::endl << "=> rend() [OK]" << std::endl;
	else
		std::cout << RED << "=> rend() [ERROR]" << std::endl;
	std::cout << "[STL] rend() = " << rend_stl << std::endl;
	std::cout << "[FT]  rend() = " << rend_ft << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator rend(): " << RESET << std::endl;
	std::vector<int>::const_reverse_iterator stl_const_rend = stl_vector_range.rend() - 1;
	ft::vector<int>::const_reverse_iterator ft_const_rend = ft_vector_range.rend() - 1;
	const int const_rend_stl = *(stl_const_rend);
	const int const_rend_ft = *(ft_const_rend);
	if (const_rend_stl == const_rend_ft)
		std::cout << GREEN << std::endl << "=> const rend() [OK]" << std::endl;
	else
		std::cout << RED << "=> const rend() [ERROR]" << std::endl;
	std::cout << "[STL] rend() = " << const_rend_stl << std::endl;
	std::cout << "[FT]  rend() = " << const_rend_ft << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Size small: " << RESET << std::endl;
	std::vector<int> stl_fill(21);
	ft::vector<int> ft_fill(21);
	checkVectorsDiff(stl_fill, ft_fill);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Size big: " << RESET << std::endl;
	std::vector<int> stl_fill2(100042);
	ft::vector<int> ft_fill2(100042);
	checkVectorsDiff(stl_fill2, ft_fill2);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Resize +++: " << RESET << std::endl;
	std::vector<int> stl_fill3(42);
	ft::vector<int> ft_fill3(42);
	stl_fill3.resize(84);
	ft_fill3.resize(84);
	checkVectorsDiff(stl_fill3, ft_fill3);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Resize ---: " << RESET << std::endl;
	std::vector<int> stl_fill4(42);
	ft::vector<int> ft_fill4(42);
	stl_fill4.resize(21);
	ft_fill4.resize(21);
	checkVectorsDiff(stl_fill4, ft_fill4);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Capacity small: " << RESET << std::endl;
	std::vector<int> stl_fill5(42);
	ft::vector<int> ft_fill5(42);
	stl_fill5.push_back(21);
	ft_fill5.push_back(21);
	stl_fill5.push_back(84);
	ft_fill5.push_back(84);
	checkVectorsDiff(stl_fill5, ft_fill5);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Capacity big: " << RESET << std::endl;
	std::vector<int> stl_fill6(42000);
	ft::vector<int> ft_fill6(42000);
	checkVectorsDiff(stl_fill6, ft_fill6);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Reserve: " << RESET << std::endl;
	std::vector<int> stl_reserve;
	ft::vector<int> ft_reserve;
	stl_reserve.reserve(42);
	ft_reserve.reserve(42);
	checkVectorsDiff(stl_reserve, ft_reserve);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Operator[]: " << RESET << std::endl;
	if (stl_vector_range[0] == ft_vector_range[0])
		std::cout << GREEN << std::endl << "=> operator[0] [OK]" << std::endl;
	else
		std::cout << RED << "=> operator[0] [ERROR]" << std::endl;
	std::cout << "[STL] operator[0] = " << stl_vector_range[0] << std::endl;
	std::cout << "[FT]  operator[0] = " << ft_vector_range[0] << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "at(4): " << RESET << std::endl;
	if (stl_vector_range.at(4) == ft_vector_range.at(4))
		std::cout << GREEN << std::endl << "=> at(4) [OK]" << std::endl;
	else
		std::cout << RED << "=> a(4) [ERROR]" << std::endl;
	std::cout << "[STL] at(4) = " << stl_vector_range.at(4) << std::endl;
	std::cout << "[FT]  at(4) = " << ft_vector_range.at(4) << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "const at(4): " << RESET << std::endl;
	const int stl_at_const = stl_vector_range.at(4);
	const int ft_at_const = ft_vector_range.at(4);
	if (stl_at_const == ft_at_const)
		std::cout << GREEN << std::endl << "=> const at(4) [OK]" << std::endl;
	else
		std::cout << RED << "=> const a(4) [ERROR]" << std::endl;
	std::cout << "[STL] const at(4) = " << stl_at_const << std::endl;
	std::cout << "[FT]  const at(4) = " << ft_at_const << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "front(): " << RESET << std::endl;
	if (stl_vector_range.front() == ft_vector_range.front())
		std::cout << GREEN << std::endl << "=> front() [OK]" << std::endl;
	else
		std::cout << RED << "=> front() [ERROR]" << std::endl;
	std::cout << "[STL] front() = " << stl_vector_range.front() << std::endl;
	std::cout << "[FT]  front() = " << ft_vector_range.front() << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "const front(): " << RESET << std::endl;
	const int stl_front_const = stl_vector_range.front();
	const int ft_front_const = ft_vector_range.front();
	if (stl_front_const == ft_front_const)
		std::cout << GREEN << std::endl << "=> const front() [OK]" << std::endl;
	else
		std::cout << RED << "=> const front() [ERROR]" << std::endl;
	std::cout << "[STL] const front() = " << stl_front_const << std::endl;
	std::cout << "[FT]  const front() = " << ft_front_const << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "back(): " << RESET << std::endl;
	if (stl_vector_range.back() == ft_vector_range.back())
		std::cout << GREEN << std::endl << "=> back() [OK]" << std::endl;
	else
		std::cout << RED << "=> back() [ERROR]" << std::endl;
	std::cout << "[STL] back() = " << stl_vector_range.back() << std::endl;
	std::cout << "[FT]  back() = " << ft_vector_range.back() << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "const back(): " << RESET << std::endl;
	const int stl_back_const = stl_vector_range.back();
	const int ft_back_const = ft_vector_range.back();
	if (stl_back_const == ft_back_const)
		std::cout << GREEN << std::endl << "=> const back() [OK]" << std::endl;
	else
		std::cout << RED << "=> const back() [ERROR]" << std::endl;
	std::cout << "[STL] const back() = " << stl_back_const << std::endl;
	std::cout << "[FT]  const back() = " << ft_back_const << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Assign range: " << RESET << std::endl;
	std::vector<int> stl_assign;
	ft::vector<int> ft_assign;
	stl_assign.assign(stl_iterator, stl_iterator + 6);
	ft_assign.assign(ft_iterator, ft_iterator + 6);
	checkVectorsDiff(stl_assign, ft_assign);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Assign range & replace: " << RESET << std::endl;
	std::vector<int> stl_assign2(42);
	ft::vector<int> ft_assign2(42);
	stl_assign2.assign(stl_iterator, stl_iterator + 6);
	ft_assign2.assign(ft_iterator, ft_iterator + 6);
	checkVectorsDiff(stl_assign2, ft_assign2);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Assign fill: " << RESET << std::endl;
	std::vector<int> stl_assign_fill;
	ft::vector<int> ft_assign_fill;
	stl_assign_fill.assign(5,6);
	ft_assign_fill.assign(5,6);
	checkVectorsDiff(stl_assign_fill, ft_assign_fill);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Assign fill & replace: " << RESET << std::endl;
	std::vector<int> stl_assign_fill2(42);
	ft::vector<int> ft_assign_fill2(42);
	stl_assign_fill2.assign(5,6);
	ft_assign_fill2.assign(5,6);
	checkVectorsDiff(stl_assign_fill2, ft_assign_fill2);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Push back empty: " << RESET << std::endl;
	std::vector<int> stl_pusback;
	ft::vector<int> ft_pusback;
	stl_pusback.push_back(4);
	ft_pusback.push_back(4);
	checkVectorsDiff(stl_pusback, ft_pusback);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Push back: " << RESET << std::endl;
	std::vector<int> stl_pusback2(2);
	ft::vector<int> ft_pusback2(2);
	stl_pusback2.push_back(4);
	ft_pusback2.push_back(4);
	checkVectorsDiff(stl_pusback2, ft_pusback2);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Pop back: " << RESET << std::endl;
	std::vector<int> stl_popback(stl_iterator, stl_iterator + 6);
	ft::vector<int> ft_popback(ft_iterator, ft_iterator + 6);
	stl_popback.pop_back();
	ft_popback.pop_back();
	checkVectorsDiff(stl_popback, ft_popback);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Insert 1 element: " << RESET << std::endl;
	std::vector<int> stl_insert(stl_iterator, stl_iterator + 6);
	ft::vector<int> ft_insert(ft_iterator, ft_iterator + 6);
	stl_insert.insert(stl_insert.begin() + 2, 5);
	ft_insert.insert(ft_insert.begin() + 2, 5);
	checkVectorsDiff(stl_insert, ft_insert);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Insert range: " << RESET << std::endl;
	std::vector<int> stl_insert2(4);
	ft::vector<int> ft_insert2(4);
	stl_insert2.insert(stl_insert2.begin() + 2, 5, 4);
	ft_insert2.insert(ft_insert2.begin() + 2, 5, 4);
	checkVectorsDiff(stl_insert, ft_insert);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Erase 1 element: " << RESET << std::endl;
	stl_insert.erase(stl_insert.begin() + 2);
	ft_insert.erase(ft_insert.begin() + 2);
	checkVectorsDiff(stl_insert, ft_insert);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Erase range: " << RESET << std::endl;
	stl_insert.erase(stl_insert.begin() + 1, stl_insert.end() - 2);
	ft_insert.erase(ft_insert.begin() + 1, ft_insert.end() - 2);
	checkVectorsDiff(stl_insert, ft_insert);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Swap: " << RESET << std::endl;
	int range_array_one[] = {1458, -98, 745, 62, 9};
	int range_array_two[] = {478, 87, -15, 44, 7};
	std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
	std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
	ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
	ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));
	std::vector<int> stl_swap_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
	std::vector<int> stl_swap_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
	ft::vector<int> ft_swap_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
	ft::vector<int> ft_swap_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);
	stl_swap_one.swap(stl_swap_two);
	ft_swap_one.swap(ft_swap_two);
	checkVectorsDiff(stl_swap_one, ft_swap_one);
	checkVectorsDiff(stl_swap_two, ft_swap_two);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Clear: " << RESET << std::endl;
	std::vector<int> stl_clear(stl_iterator, stl_iterator + 5);
	ft::vector<int> ft_clear(ft_iterator, ft_iterator + 5);
	stl_clear.clear();
	ft_clear.clear();
	checkVectorsDiff(stl_clear, ft_clear);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "SWAP: " << RESET << std::endl;
	std::swap(stl_swap_one, stl_swap_two);
    ft::swap(ft_swap_one, ft_swap_two);
	checkVectorsDiff(stl_swap_one, ft_swap_one);
	checkVectorsDiff(stl_swap_two, ft_swap_two);
	std::cin.get();
}
