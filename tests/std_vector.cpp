#include <iostream>
#include <string>
#include <deque>
#include <stdlib.h>

#include <vector>
namespace ft = std;

int main(int argc, char** argv) {
	ft::vector<int> vector_int;


    srand(123);
    std::cout << "vector is empty" << std::endl;
    std::cout << vector_int.empty() << std::endl;

    for(int i = 0; i <= 100000000; i++)
        vector_int.push_back(rand());
   	ft::vector<int> copy_vector_int = vector_int;

    std::cout << "vector/copy vector is empty" << std::endl;
    std::cout << vector_int.empty() << std::endl;
    std::cout << copy_vector_int.empty() << std::endl;

    std::cout << "vector/copy vector max size" << std::endl;
    std::cout << vector_int.max_size() << std::endl;
    std::cout << copy_vector_int.max_size() << std::endl;

    std::cout << "vector/copy vector size" << std::endl;
    std::cout << vector_int.size() << std::endl;
    std::cout << copy_vector_int.size() << std::endl;

    std::cout << "vector/copy vector capacity" << std::endl;
    std::cout << vector_int.capacity() << std::endl;
    std::cout << copy_vector_int.capacity() << std::endl;

    std::cout << "vector/copy vector front" << std::endl;
    std::cout << vector_int.front() << std::endl;
    std::cout << copy_vector_int.front() << std::endl;

    std::cout << "vector/copy vector data" << std::endl;
    for(int i = 124300; i <= 124310; i++)
     std::cout << vector_int[i] << std::endl;
    std::cout << "################" << std::endl;
    for(int i = 124300; i <= 124310; i++)
     std::cout << copy_vector_int[i] << std::endl;
    std::cout << "################" << std::endl;

    std::cout << "pop_back 100" << std::endl;
    for(int i = 154300; i <= 154400; i++)
     vector_int.pop_back();
    std::cout << "push_back 100" << std::endl;
    for(int i = 154300; i <= 154410; i++)
     vector_int.push_back();



}