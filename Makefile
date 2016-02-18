# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jquilez <jquilez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/20 09:58:45 by jquilez           #+#    #+#              #
#    Updated: 2015/03/21 20:09:38 by jmaurice         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#General
CC			= /usr/bin/g++
CFLAGS		= -Wall -Wextra -O3 -std=c++11
INC 		= -I ./inc -I ~/.brew/include/

#Messages
MSG_OTHER	= @echo "\033[33m[build]  " | tr -d '\n'
MSG_BUILD	= @echo "\033[32m[build]  " | tr -d '\n'
MSG_DELETE	= @echo "\033[31m[delete] " | tr -d '\n'
NSG_CLOSE	= @echo "\033[0m" | tr -d '\n'

#Files
NAME		= npuzzle
FILES		= main.cpp
FILES		+= Parser.cpp
FILES		+= Generator.cpp
FILES		+= ACreate.cpp
FILES		+= Puzzle.cpp
FILES		+= Ai.cpp
SRC			= $(addprefix ./src/, $(FILES))
OBJET		= $(FILES:.cpp=.o)

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(OBJET)
	$(MSG_BUILD)
	$(CC) -o $(NAME) $(OBJET) $(CFLAGS)
	$(MSG_CLOSE)

$(OBJET): $(SRC)
	$(MSG_OTHER)
	$(CC) -c $^ $(CFLAGS) $(INC)
	$(MSG_CLOSE)

clean:
	$(MSG_DELETE)
	/bin/rm -f $(OBJET)
	$(MSG_CLOSE)

fclean: clean
	$(MSG_DELETE)
	/bin/rm -f $(NAME)
	$(MSG_CLOSE)

re: fclean all
