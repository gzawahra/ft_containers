#!/bin/bash
echo "----------- 42 main tests ----------- "
echo "-----------    STD TEST   ----------- "
g++ -std=c++98 ./tests/std_main.cpp
time ./a.out 123
rm -rf a.out
echo "-----------     FT TEST    ----------- "
g++ -std=c++98 ./tests/ft_main.cpp
time ./a.out 123
rm -rf a.out
echo
echo "-----------  Vector tests  ----------- "
echo "-----------    STD TEST    ----------- "
g++ -std=c++98 ./tests/std_vector.cpp
time ./a.out 123
rm -rf a.out
echo "-----------     FT TEST    ----------- "
g++ -std=c++98 ./tests/ft_vector.cpp
time ./a.out 123
rm -rf a.out
echo "-----------  Stack tests  ----------- "
echo "-----------    STD TEST   ----------- "
g++ -std=c++98 ./tests/std_stack.cpp
time ./a.out 123
rm -rf a.out
echo "-----------     FT TEST    ----------- "
g++ -std=c++98 ./tests/ft_stack.cpp
time ./a.out 123
rm -rf a.out
echo "-----------    Map tests   ----------- "
echo "-----------    STD TEST    ----------- "
g++ -std=c++98 ./tests/std_map.cpp
time ./a.out 123
rm -rf a.out
echo "-----------     FT TEST    ----------- "
g++ -std=c++98 ./tests/ft_map.cpp
time ./a.out 123
rm -rf a.out
echo "-----------       END      ----------- "