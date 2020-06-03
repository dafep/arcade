##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

ECHO 			= 			/bin/echo -e
D         		=       	"\033[00m"
G	            =       	"\033[0;32m"
R	            =    	    "\033[1;31m"

RM		=	rm -r -f

NAME	=	arcade

SRC		=	main.cpp 						\
			./build/IGameCore.cpp 			\
			./build/Err.cpp

OBJ		=	$(SRC:.cpp=.o)

CFLAGS	+=	-ISources-W -Wextra -Wall -W -I./include

LDFLAGS	=	-std=c++17 -lstdc++ -O3 -ldl -lncurses -lsfml-window -lsfml-system -lsfml-audio -lsfml-network \
			-lsfml-graphics -lcaca -Iinclude -lsfml-network

$(NAME):	$(OBJ)
			g++ -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

debug:		CFLAGS += -g
debug:		re

all:		$(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY :    all clean fclean re