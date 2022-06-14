STL		=	1

FT		=	1

NAME	=	ft_containers

ifeq ($(STL), 1)
	ifeq ($(FT), 0)
		SRCS	=	tests/main_stl.cpp
		NAME	=	binary_stl
	else
		SRCS	=	tests/main.cpp	\
					tests/map_test.cpp \
					tests/vector_test.cpp \
					tests/stack_test.cpp
	endif
endif

ifeq ($(FT), 1)
	ifeq ($(STL), 0)
		SRCS	=	tests/main_ft.cpp
		NAME	=	binary_ft
	endif
endif

OBJS	=	$(SRCS:.cpp=.o)

CC		=	clang++

CFLAGS	=	-Wall -Werror -Wextra -std=c++98

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.cpp
			$(CC) $(CFLAGS) -o $@ -c $<

clean:
			rm -f $(OBJS)

fclean: 	clean
			rm -f $(NAME)

re: 		fclean all

.PHONY: 	clean all fclean re