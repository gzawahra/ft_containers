# include <stack>
# include <fstream>
# include <cstring>
# include <iostream>

# include "../stack.hpp"

// Linux Colors
# define RESET "\e[0m"
# define BOLD "\e[1m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define BLUE "\e[34m"
# define PINK "\e[35m"

template <class T>
void checkStacksDiff(std::stack<T>& stl_stack, ft::stack<T>& ft_stack)
{
	if (stl_stack.size() == ft_stack.size())
		std::cout << GREEN << std::endl << "=> size() [OK]" << std::endl;
	else
		std::cout << RED << "size() [ERROR]" << std::endl;
	std::cout << "[STL] Size = " << stl_stack.size() << std::endl;
	std::cout << "[FT]  Size = " << ft_stack.size() << std::endl;

	if (stl_stack.empty() == ft_stack.empty())
		std::cout << GREEN << std::endl << "=> empty() [OK]" << std::endl;
	else
		std::cout << RED << "empty() [ERROR]" << std::endl;
	std::cout << "[STL] Empty = " << stl_stack.empty() << std::endl;
	std::cout << "[FT]  Empty = " << ft_stack.empty() << std::endl << std::endl;
	
	std::cout << RESET << "[STL] Content = [";
	while (42)
	{
		if (stl_stack.size() == 0)
			break;
		std::cout << stl_stack.top();
		stl_stack.pop();
		if (stl_stack.size() != 0)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;
	std::cout << "[FT]  Content = [";
	while (42)
	{
		if (ft_stack.size() == 0)
			break;
		std::cout << ft_stack.top();
		ft_stack.pop();
		if (ft_stack.size() != 0)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl << std::endl;
}

void stack_test()
{
	std::cout << BOLD << "STACK TESTS: " << RESET << std::endl;

	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Default constructor: " << RESET << std::endl;
	std::stack<int> stl_stack;
	ft::stack<int> ft_stack;
	checkStacksDiff(stl_stack, ft_stack);
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Push: " << RESET << std::endl;
	for (int i = 0; i < 3; i++)
	{
		stl_stack.push(i);
		ft_stack.push(i);
	}
	std::cout << GREEN << std::endl << "=> push() [OK]" << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Top: " << RESET << std::endl;
	if (stl_stack.top() == ft_stack.top())
		std::cout << GREEN << std::endl << "=> top() [OK]" << std::endl;
	else
		std::cout << RED << "=> top() [ERROR]" << std::endl;
	std::cout << "[STL] top() = " << stl_stack.top() << std::endl;
	std::cout << "[FT]  top() = " << ft_stack.top() << std::endl << std::endl;
	std::cin.get();
	
	std::cout << RESET << BOLD << "==============================" << std::endl;
	std::cout << std::endl << "Pop: " << RESET << std::endl;
	for (int i = 0; i < 5; ++i)
	{
		stl_stack.push(i);
		ft_stack.push(i);
	}
	std::cout << "[STL] Popping out elements...";
	while (!stl_stack.empty())
	{
		std::cout << ' ' << stl_stack.top();
		stl_stack.pop();
	}
	std::cout << std::endl;
	std::cout << "[FT]  Popping out elements...";
	while (!ft_stack.empty())
	{
		std::cout << ' ' << ft_stack.top();
		ft_stack.pop();
	}
	std::cout << std::endl;
	std::cin.get();
}
