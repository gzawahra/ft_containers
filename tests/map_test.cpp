# include <map>
# include <fstream>
# include <cstring>
# include <iostream>

# include "../map.hpp"

// Linux Colors
# define RESET "\e[0m"
# define BOLD "\e[1m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define BLUE "\e[34m"
# define PINK "\e[35m"


template <class T1, class T2>
void checkMapsDiff(std::map<T1, T2>& stl_map, ft::map<T1, T2>& ft_map)
{
	if (stl_map.size() == ft_map.size())
		std::cout << GREEN << std::endl << "=> size() [OK]" << std::endl;
	else
		std::cout << RED << "size() [ERROR]" << std::endl;
	std::cout << "[STL] Size = " << stl_map.size() << std::endl;
	std::cout << "[FT]  Size = " << ft_map.size() << std::endl;

	if (stl_map.max_size() == ft_map.max_size())
		std::cout << GREEN << std::endl << "=> max_size() [OK]" << std::endl;
	else
		std::cout << RED << "max_size() [ERROR]" << std::endl;
	std::cout << "[STL] Max Size = " << stl_map.max_size() << std::endl;
	std::cout << "[FT]  Max Size = " << ft_map.max_size() << std::endl;

	if (stl_map.empty() == ft_map.empty())
		std::cout << GREEN << std::endl << "=> empty() [OK]" << std::endl;
	else
		std::cout << RED << "empty() [ERROR]" << std::endl;
	std::cout << "[STL] Empty = " << stl_map.empty() << std::endl;
	std::cout << "[FT]  Empty = " << ft_map.empty() << std::endl << std::endl;
	
	std::cout << RESET << "[STL] Content = [";
	typename std::map<T1, T2>::const_iterator stl_it;
	for (stl_it = stl_map.begin(); stl_it != stl_map.end(); stl_it++)
	{
		std::cout << "{" << (*stl_it).first << ", " << (*stl_it).second << "}, ";
	}
	std::cout << "]" << std::endl;
	std::cout << "[FT]  Content = [";
	typename ft::map<T1, T2>::const_iterator ft_it;
	for (ft_it = ft_map.begin(); ft_it != ft_map.end(); ft_it++)
	{
		std::cout << "{" << (*ft_it).first << ", " << (*ft_it).second << "}, ";
	}
	std::cout << "]" << std::endl << std::endl;
}

void map_test()
{
	std::cout << BOLD << "MAP TESTS: " << RESET << std::endl;

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Default constructor: " << RESET << std::endl;
	std::map<int, std::string> stl_default_map;
	ft::map<int, std::string> ft_default_map;
	checkMapsDiff(stl_default_map, ft_default_map);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Range constructor: " << RESET << std::endl;
	const int range_int[] = {-420, -42, 0, 42, -420};
	const std::string range_str[] = {"Yes", "No", "Why", "idk", "forty-two"};
	std::map<int, std::string> stl_map;
	ft::map<int, std::string> ft_map;
	for (int i = 0; i < 5; i++)
	{
		stl_map.insert(std::make_pair(range_int[i], range_str[i]));
		ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
	}
	checkMapsDiff(stl_map, ft_map);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Copy constructor: " << RESET << std::endl;
	std::map<int, std::string> stl_map_copy(stl_map);
	ft::map<int, std::string> ft_map_copy(ft_map);
	checkMapsDiff(stl_map_copy, ft_map_copy);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Assign constructor: " << RESET << std::endl;
	std::map<int, std::string> stl_map_assign = stl_map;
	ft::map<int, std::string> ft_map_assign = ft_map;
	checkMapsDiff(stl_map_assign, ft_map_assign);

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator Begin(): " << RESET << std::endl;
	if ((*stl_map.begin()).first == (*ft_map.begin()).first)
		std::cout << GREEN << std::endl << "=> begin() first [OK]" << std::endl;
	else
		std::cout << RED << "=> begin() first [ERROR]" << std::endl;
	std::cout << "[STL] begin().first = " << (*stl_map.begin()).first << std::endl;
	std::cout << "[FT]  begin().first = " << (*ft_map.begin()).first << std::endl << std::endl;
	if ((*stl_map.begin()).second == (*ft_map.begin()).second)
		std::cout << GREEN << std::endl << "=> begin() second [OK]" << std::endl;
	else
		std::cout << RED << "=> begin() second [ERROR]" << std::endl;
	std::cout << "[STL] begin().second = " << (*stl_map.begin()).second << std::endl;
	std::cout << "[FT]  begin().second = " << (*ft_map.begin()).second << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator Begin(): " << RESET << std::endl;
	std::map<int, std::string>::const_iterator stl_map_const = stl_map.begin();
	ft::map<int, std::string>::const_iterator ft_map_const = ft_map.begin();
	if ((*stl_map_const).first == (*ft_map_const).first)
		std::cout << GREEN << std::endl << "=> const begin() first [OK]" << std::endl;
	else
		std::cout << RED << "=> const begin() first [ERROR]" << std::endl;
	std::cout << "[STL] const begin().first = " << (*stl_map_const).first << std::endl;
	std::cout << "[FT]  const begin().first = " << (*ft_map_const).first << std::endl << std::endl;
	if ((*stl_map_const).second == (*ft_map_const).second)
		std::cout << GREEN << std::endl << "=> const begin() second [OK]" << std::endl;
	else
		std::cout << RED << "=> const begin() second [ERROR]" << std::endl;
	std::cout << "[STL] const begin().second = " << (*stl_map_const).second << std::endl;
	std::cout << "[FT]  const begin().second = " << (*ft_map_const).second << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator End(): " << RESET << std::endl;
	if ((*stl_map.end()).first == (*ft_map.end()).first)
		std::cout << GREEN << std::endl << "=> end() first [OK]" << std::endl;
	else
		std::cout << RED << "=> end() first [ERROR]" << std::endl;
	std::cout << "[STL] end().first = " << (*stl_map.end()).first << std::endl;
	std::cout << "[FT]  end().first = " << (*ft_map.end()).first << std::endl << std::endl;
	if ((*stl_map.end()).second == (*ft_map.end()).second)
		std::cout << GREEN << std::endl << "=> end() second [OK]" << std::endl;
	else
		std::cout << RED << "=> end() second [ERROR]" << std::endl;
	std::cout << "[STL] end().second = " << (*stl_map.end()).second << std::endl;
	std::cout << "[FT]  end().second = " << (*ft_map.end()).second << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator End(): " << RESET << std::endl;
	std::map<int, std::string>::const_iterator stl_map_const2 = stl_map.end();
	ft::map<int, std::string>::const_iterator ft_map_const2 = ft_map.end();
	if ((*stl_map_const2).first == (*ft_map_const2).first)
		std::cout << GREEN << std::endl << "=> const end() first [OK]" << std::endl;
	else
		std::cout << RED << "=> const end() first [ERROR]" << std::endl;
	std::cout << "[STL] const end().first = " << (*stl_map_const2).first << std::endl;
	std::cout << "[FT]  const end().first = " << (*ft_map_const2).first << std::endl << std::endl;
	if ((*stl_map_const2).second == (*ft_map_const2).second)
		std::cout << GREEN << std::endl << "=> const end() second [OK]" << std::endl;
	else
		std::cout << RED << "=> const end() second [ERROR]" << std::endl;
	std::cout << "[STL] const end().second = " << (*stl_map_const2).second << std::endl;
	std::cout << "[FT]  const end().second = " << (*ft_map_const2).second << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator rbegin(): " << RESET << std::endl;
	if ((*stl_map.rbegin()).first == (*ft_map.rbegin()).first)
		std::cout << GREEN << std::endl << "=> rbegin() first [OK]" << std::endl;
	else
		std::cout << RED << "=> rbegin() first [ERROR]" << std::endl;
	std::cout << "[STL] rbegin().first = " << (*stl_map.rbegin()).first << std::endl;
	std::cout << "[FT]  rbegin().first = " << (*ft_map.rbegin()).first << std::endl << std::endl;
	if ((*stl_map.rbegin()).second == (*ft_map.rbegin()).second)
		std::cout << GREEN << std::endl << "=> rbegin() second [OK]" << std::endl;
	else
		std::cout << RED << "=> rbegin() second [ERROR]" << std::endl;
	std::cout << "[STL] rbegin().second = " << (*stl_map.rbegin()).second << std::endl;
	std::cout << "[FT]  rbegin().second = " << (*ft_map.rbegin()).second << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator rbegin(): " << RESET << std::endl;
	std::map<int, std::string>::const_reverse_iterator stl_map_const3 = stl_map.rbegin();
	ft::map<int, std::string>::const_reverse_iterator ft_map_const3 = ft_map.rbegin();
	if ((*stl_map_const3).first == (*ft_map_const3).first)
		std::cout << GREEN << std::endl << "=> const rbegin() first [OK]" << std::endl;
	else
		std::cout << RED << "=> const rbegin() first [ERROR]" << std::endl;
	std::cout << "[STL] const rbegin().first = " << (*stl_map_const3).first << std::endl;
	std::cout << "[FT]  const rbegin().first = " << (*ft_map_const3).first << std::endl << std::endl;
	if ((*stl_map_const3).second == (*ft_map_const3).second)
		std::cout << GREEN << std::endl << "=> const rbegin() second [OK]" << std::endl;
	else
		std::cout << RED << "=> const rbegin() second [ERROR]" << std::endl;
	std::cout << "[STL] const rbegin().second = " << (*stl_map_const3).second << std::endl;
	std::cout << "[FT]  const rbegin().second = " << (*ft_map_const3).second << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator rend(): " << RESET << std::endl;
	if ((*stl_map.rend()).first == (*ft_map.rend()).first)
		std::cout << GREEN << std::endl << "=> rend() first [OK]" << std::endl;
	else
		std::cout << RED << "=> rend() first [ERROR]" << std::endl;
	std::cout << "[STL] rend().first = " << (*stl_map.rend()).first << std::endl;
	std::cout << "[FT]  rend().first = " << (*ft_map.rend()).first << std::endl << std::endl;
	if ((*stl_map.rend()).second == (*ft_map.rend()).second)
		std::cout << GREEN << std::endl << "=> rend() second [OK]" << std::endl;
	else
		std::cout << RED << "=> rend() second [ERROR]" << std::endl;
	std::cout << "[STL] rend().second = " << (*stl_map.rend()).second << std::endl;
	std::cout << "[FT]  rend().second = " << (*ft_map.rend()).second << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator rend(): " << RESET << std::endl;
	std::map<int, std::string>::const_reverse_iterator stl_map_const4 = stl_map.rend();
	ft::map<int, std::string>::const_reverse_iterator ft_map_const4 = ft_map.rend();
	if ((*stl_map_const4).first == (*ft_map_const4).first)
		std::cout << GREEN << std::endl << "=> const rend() first [OK]" << std::endl;
	else
		std::cout << RED << "=> const rend() first [ERROR]" << std::endl;
	std::cout << "[STL] const rend().first = " << (*stl_map_const4).first << std::endl;
	std::cout << "[FT]  const rend().first = " << (*ft_map_const4).first << std::endl << std::endl;
	if ((*stl_map_const4).second == (*ft_map_const4).second)
		std::cout << GREEN << std::endl << "=> const rend() second [OK]" << std::endl;
	else
		std::cout << RED << "=> const rend() second [ERROR]" << std::endl;
	std::cout << "[STL] const rend().second = " << (*stl_map_const4).second << std::endl;
	std::cout << "[FT]  const rend().second = " << (*ft_map_const4).second << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator operator[]: " << RESET << std::endl;
	if (stl_map[-9] == ft_map[-9])
		std::cout << GREEN << std::endl << "=> const operator[] test 1 [OK]" << std::endl;
	else
		std::cout << RED << "=> const operator[] test 1 [ERROR]" << std::endl;
	stl_map[-9] = "test";
	ft_map[-9] = "test";
	if (stl_map[-9] == ft_map[-9])
		std::cout << GREEN << std::endl << "=> const operator[] test 2 [OK]" << std::endl;
	else
		std::cout << RED << "=> const operator[] test 2 [ERROR]" << std::endl;
	std::cout << "[STL] stl_map[-9] = " << stl_map[-9] << std::endl;
	std::cout << "[FT]  stl_map[-9] = " << ft_map[-9] << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Insert: " << RESET << std::endl;
	stl_map.insert(std::make_pair(1234, "42"));
	ft_map.insert(ft::make_pair(1234, "42"));
	checkMapsDiff(stl_map, ft_map);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Insert Range: " << RESET << std::endl;
	stl_map.insert(stl_map.begin(), stl_map.begin());
	ft_map.insert(ft_map.begin(), ft_map.begin());
	checkMapsDiff(stl_map, ft_map);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Erase (begin): " << RESET << std::endl;
	stl_map.erase(stl_map.begin());
	ft_map.erase(ft_map.begin());
	checkMapsDiff(stl_map, ft_map);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Erase key (42): " << RESET << std::endl;
	stl_map.erase(42);
	ft_map.erase(42);
	checkMapsDiff(stl_map, ft_map);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Swap: " << RESET << std::endl;
	stl_map.swap(stl_map_copy);
	ft_map.swap(ft_map_copy);
	checkMapsDiff(stl_map, ft_map);
	checkMapsDiff(stl_map_copy, ft_map_copy);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Clear: " << RESET << std::endl;
	stl_map.clear();
	ft_map.clear();
	checkMapsDiff(stl_map, ft_map);
	std::cin.get();
}
