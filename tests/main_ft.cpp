# include <fstream>
# include <cstring>
# include <iostream>

# include "../stack.hpp"
# include "../map.hpp"
# include "../vector.hpp"


// Linux Colors
# define RESET "\e[0m"
# define BOLD "\e[1m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define BLUE "\e[34m"
# define PINK "\e[35m"


template <class T>
void print_stack(ft::stack<T>& stack)
{
	std::cout << "Size = " << stack.size() << std::endl;
	std::cout << "Empty = " << stack.empty() << std::endl;
	std::cout << RESET << "Content = [";
	while (42)
	{
		if (stack.size() == 0)
			break;
		std::cout << stack.top();
		stack.pop();
		if (stack.size() != 0)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl << std::endl;
}

template <class T1, class T2>
void print_map(ft::map<T1, T2>& map)
{
	std::cout << "Size = " << map.size() << std::endl;
	std::cout << "Max Size = " << map.max_size() << std::endl;
	std::cout << "Empty = " << map.empty() << std::endl;
	std::cout << "Content = [";
	typename ft::map<T1, T2>::const_iterator it;
	for (it = map.begin(); it != map.end(); it++)
	{
		std::cout << "{" << (*it).first << ", " << (*it).second << "}, ";
	}
	std::cout << "]" << std::endl << std::endl;
}



template <class T>
void print_vector(ft::vector<T>& vector)
{
	std::cout << "Size = " << vector.size() << std::endl;
	std::cout << "Max Size = " << vector.max_size() << std::endl;
	std::cout << "Max Size = " << vector.capacity() << std::endl;
	std::cout << "Empty = " << vector.empty() << std::endl;
	std::cout << "Content = [";
	typename ft::vector<T>::const_iterator it;
	for (it = vector.begin(); it != vector.end(); it++)
	{
		std::cout << *it;
		if (it + 1 != vector.end())
			std::cout << ", ";
	}
	std::cout << "]" << std::endl << std::endl;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
	
	std::cout << BLUE BOLD << "__FT__ " << RESET << std::endl;

    std::cout << BOLD << "VECTOR TESTS: " << RESET << std::endl;

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Default constructor: " << RESET << std::endl;
	ft::vector<int> vector_int;
	print_vector(vector_int);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Default constructor pointer: " << RESET << std::endl;
	ft::vector<int> *vector_int_p = new ft::vector<int>;
	print_vector(*vector_int_p);
	delete vector_int_p;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Fill constructor: " << RESET << std::endl;
	ft::vector<int> vector_fill(0);
	print_vector(vector_fill);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Fill constructor sized: " << RESET << std::endl;
	ft::vector<int> vector_fill_sized(42);
	print_vector(vector_fill_sized);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Fill constructor sized + value: " << RESET << std::endl;
	ft::vector<int> vector_fill_sizedv(42, 42);
	print_vector(vector_fill_sizedv);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Range constructor: " << RESET << std::endl;
	int range_array[] = {42, 21, 123456, 0, 4, 13};
	ft::vector<int>::iterator iterator(&(range_array[0]));
	ft::vector<int> vector_range(iterator, iterator + 6);
	print_vector(vector_range);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Copy constructor: " << RESET << std::endl;
	ft::vector<int> vector_copy(vector_range);
	print_vector(vector_copy);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Assign constructor: " << RESET << std::endl;
	ft::vector<int> vector_assign = vector_range;
	print_vector(vector_assign);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator begin(): " << RESET << std::endl;
	int begin = *(vector_range.begin());
	std::cout << "begin() = " << begin << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator begin(): " << RESET << std::endl;
	ft::vector<int>::const_iterator const_it = vector_range.begin();
	const int const_begin = *(const_it);
	std::cout << "begin() = " << const_begin << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator end(): " << RESET << std::endl;
	int end = *(vector_range.end() - 1);
	std::cout << "end() = " << end << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator end(): " << RESET << std::endl;
	ft::vector<int>::const_iterator const_end = vector_range.end() - 1;
	const int const_end2 = *(const_end);
	std::cout << "end() = " << const_end2 << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator rbegin(): " << RESET << std::endl;
	int rbegin = *(vector_range.rbegin());
	std::cout << "rbegin() = " << rbegin << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator rbegin(): " << RESET << std::endl;
	ft::vector<int>::const_reverse_iterator const_rbegin = vector_range.rbegin();
	const int const_rbegin_stl = *(const_rbegin);
	std::cout << "cosnt rbegin() = " << const_rbegin_stl << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator rend(): " << RESET << std::endl;
	int rend_stl = *(vector_range.rend() - 1);
	std::cout << "rend() = " << rend_stl << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator rend(): " << RESET << std::endl;
	ft::vector<int>::const_reverse_iterator const_rend = vector_range.rend() - 1;
	const int const_rend_stl = *(const_rend);
	std::cout << "rend() = " << const_rend_stl << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Size small: " << RESET << std::endl;
	ft::vector<int> fill(21);
    print_vector(fill);
    std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Size big: " << RESET << std::endl;
	ft::vector<int> fill2(100042);
    print_vector(fill2);
    std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Resize +++: " << RESET << std::endl;
	ft::vector<int> fill3(42);
	fill3.resize(84);
	print_vector(fill3);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Resize ---: " << RESET << std::endl;
	ft::vector<int> fill4(42);
	fill4.resize(21);
	print_vector(fill4);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Capacity small: " << RESET << std::endl;
	ft::vector<int> fill5(42);
	fill5.push_back(21);
	fill5.push_back(84);
	print_vector(fill5);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Capacity big: " << RESET << std::endl;
	ft::vector<int> fill6(42000);
	print_vector(fill6);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Reserve: " << RESET << std::endl;
	ft::vector<int> reserve;
	reserve.reserve(42);
	print_vector(reserve);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Operator[]: " << RESET << std::endl;
	std::cout << "operator[0] = " << vector_range[0] << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "at(4): " << RESET << std::endl;
	std::cout << "at(4) = " << vector_range.at(4) << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "const at(4): " << RESET << std::endl;
	const int at_const = vector_range.at(4);
	std::cout << "const at(4) = " << at_const << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "front(): " << RESET << std::endl;
	std::cout << "front() = " << vector_range.front() << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "const front(): " << RESET << std::endl;
	const int front_const = vector_range.front();
	std::cout << "const front() = " << front_const << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "back(): " << RESET << std::endl;
	std::cout << "back() = " << vector_range.back() << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "const back(): " << RESET << std::endl;
	const int back_const = vector_range.back();
	std::cout << "const back() = " << back_const << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Assign range: " << RESET << std::endl;
	ft::vector<int> assign;
	assign.assign(iterator, iterator + 6);
	print_vector(assign);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Assign range & replace: " << RESET << std::endl;
	ft::vector<int> assign2(42);
	assign2.assign(iterator, iterator + 6);
	print_vector(assign2);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Assign fill: " << RESET << std::endl;
	ft::vector<int> assign_fill;
	assign_fill.assign(5,6);
	print_vector(assign_fill);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Assign fill & replace: " << RESET << std::endl;
	ft::vector<int> assign_fill2(42);
	assign_fill2.assign(5,6);
	print_vector(assign_fill2);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Push back empty: " << RESET << std::endl;
	ft::vector<int> pusback;
	pusback.push_back(4);
	print_vector(pusback);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Push back: " << RESET << std::endl;
	ft::vector<int> pusback2(2);
	pusback2.push_back(4);
	print_vector(pusback2);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Pop back: " << RESET << std::endl;
	ft::vector<int> popback(iterator, iterator + 6);
	popback.pop_back();
	print_vector(popback);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Insert 1 element: " << RESET << std::endl;
	ft::vector<int> insert(iterator, iterator + 6);
	insert.insert(insert.begin() + 2, 5);
	print_vector(insert);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Insert range: " << RESET << std::endl;
	ft::vector<int> insert2(4);
	insert2.insert(insert2.begin() + 2, 5, 4);
	print_vector(insert);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Erase 1 element: " << RESET << std::endl;
	insert.erase(insert.begin() + 2);
	print_vector(insert);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Erase range: " << RESET << std::endl;
	insert.erase(insert.begin() + 1, insert.end() - 2);
	print_vector(insert);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Swap: " << RESET << std::endl;
	int range_array_one[] = {1458, -98, 745, 62, 9};
	int range_array_two[] = {478, 87, -15, 44, 7};
	ft::vector<int>::iterator iterator_beg_one(&(range_array_one[0]));
	ft::vector<int>::iterator iterator_beg_two(&(range_array_two[0]));
	ft::vector<int> swap_one(iterator_beg_one, iterator_beg_one + 5);
	ft::vector<int> swap_two(iterator_beg_two, iterator_beg_two + 5);
	swap_one.swap(swap_two);
	print_vector(swap_one);
	print_vector(swap_two);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Clear: " << RESET << std::endl;
	ft::vector<int> clear(iterator, iterator + 5);
	clear.clear();
	print_vector(clear);
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "SWAP: " << RESET << std::endl;
	std::swap(swap_one, swap_two);
	print_vector(swap_one);
	print_vector(swap_two);
	std::cin.get();

	std::cout << BOLD << "MAP TESTS: " << RESET << std::endl;

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Default constructor: " << RESET << std::endl;
	ft::map<int, std::string> default_map;
	print_map(default_map);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Range constructor: " << RESET << std::endl;
	const int range_int[] = {-420, -42, 0, 42, -420};
	const std::string range_str[] = {"Yes", "No", "Why", "idk", "forty-two"};
	ft::map<int, std::string> map;
	for (int i = 0; i < 5; i++)
		map.insert(ft::make_pair(range_int[i], range_str[i]));
	print_map(map);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Copy constructor: " << RESET << std::endl;
	ft::map<int, std::string> map_copy(map);
	print_map(map_copy);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Assign constructor: " << RESET << std::endl;
	ft::map<int, std::string> map_assign = map;
	print_map(map_assign);

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator Begin(): " << RESET << std::endl;
	std::cout << "begin().first = " << (*map.begin()).first << std::endl;
	std::cout << "begin().second = " << (*map.begin()).second << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator Begin(): " << RESET << std::endl;
	ft::map<int, std::string>::const_iterator map_const = map.begin();
	std::cout << "const begin().first = " << (*map_const).first << std::endl;
	std::cout << "const begin().second = " << (*map_const).second << std::endl << std::endl;
	std::cin.get();

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator End(): " << RESET << std::endl;
	std::cout << "end().first = " << (*map.end()).first << std::endl;
	// std::cout << "end().second = " << (*map.end()).second << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator End(): " << RESET << std::endl;
	ft::map<int, std::string>::const_iterator map_const2 = map.end();
	std::cout << "const end().first = " << (*map_const2).first << std::endl;
	// std::cout << "const end().second = " << (*map_const2).second << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator rbegin(): " << RESET << std::endl;
	std::cout << "rbegin().first = " << (*map.rbegin()).first << std::endl;
	std::cout << "rbegin().second = " << (*map.rbegin()).second << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator rbegin(): " << RESET << std::endl;
	ft::map<int, std::string>::const_reverse_iterator map_const3 = map.rbegin();
	std::cout << "const rbegin().first = " << (*map_const3).first << std::endl;
	std::cout << "const rbegin().second = " << (*map_const3).second << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator rend(): " << RESET << std::endl;
	std::cout << "rend().first = " << (*map.rend()).first << std::endl;
	// std::cout << "rend().second = " << (*map.rend()).second << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Const Iterator rend(): " << RESET << std::endl;
	ft::map<int, std::string>::const_reverse_iterator map_const4 = map.rend();
	std::cout << "const rend().first = " << (*map_const4).first << std::endl;
	// std::cout << "const rend().second = " << (*map_const4).second << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Iterator operator[]: " << RESET << std::endl;
	map[-9] = "test";
	std::cout << "map[-9] = " << map[-9] << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Insert: " << RESET << std::endl;
	map.insert(ft::make_pair(1234, "42"));
	print_map(map);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Insert Range: " << RESET << std::endl;
	map.insert(map.begin(), map.begin());
	print_map(map);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Erase (begin): " << RESET << std::endl;
	map.erase(map.begin());
	print_map(map);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Erase key (42): " << RESET << std::endl;
	map.erase(42);
	print_map(map);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Swap: " << RESET << std::endl;
	map.swap(map_copy);
	print_map(map);
	print_map(map_copy);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Clear: " << RESET << std::endl;
	map.clear();
	print_map(map);
	std::cin.get();
    


    



    std::cout << BOLD << "STACK TESTS: " << RESET << std::endl;

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Default constructor: " << RESET << std::endl;
	ft::stack<int> stack;
	print_stack(stack);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Push: " << RESET << std::endl;
	for (int i = 0; i < 3; i++)
		stack.push(i);
	print_stack(stack);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Top: " << RESET << std::endl;
	std::cout << "top() = " << stack.top() << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Pop: " << RESET << std::endl;
	for (int i = 0; i < 5; ++i)
		stack.push(i);
	std::cout << "Popping out elements...";
	while (!stack.empty())
	{
		std::cout << ' ' << stack.top();
		stack.pop();
	}
	std::cout << std::endl;
	std::cin.get();
    
    return (0);
}