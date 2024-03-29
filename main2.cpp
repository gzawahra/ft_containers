#include <iostream>
#include <string>
#include <deque>
#include <chrono>
#include <thread>
#if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {
				//std::cout << "destructmutant" << std::endl;
	}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::nanoseconds;
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);
	//std::cout << 82 << std::endl;
	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	// std::cout << 96 << std::endl;
	for (int i = 0; i < COUNT; ++i)
	{
			// std::cout << i ;
			// std::cout << " / ";
			// std::cout << COUNT << std::endl;
     	// auto t1 = high_resolution_clock::now();
		map_int.insert(ft::make_pair(rand(), rand()));
		//ft::make_pair(rand(), rand());
    	// auto t2 = high_resolution_clock::now();
  		// auto ms_int = duration_cast<nanoseconds>(t2 - t1);
    //	std::cout << ms_int.count() << " -- 3rd ns\n";
	}
	// std::cout << 109 << std::endl;
	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;
		//std::cout << 116 << std::endl;
	{
		ft::map<int, int> copy = map_int;
	}
		//std::cout << 120 << std::endl;
	MutantStack<char> iterable_stack;
		//	std::cout << 123 << std::endl;
	for (char letter = 'a'; letter <= 'z'; letter++)
	 	iterable_stack.push(letter);
		//std::cout << 125 << std::endl;
		int i = 0 ;
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{

		std::cout << *it;
		 //std::cout << i << std::endl;
			i++;
	}
	//	std::cout << 130 << std::endl;
	std::cout << std::endl;
	//	std::cout << 133 << std::endl;
	return (0);
}