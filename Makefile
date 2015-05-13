# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdannapp <cdannapp@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/12 19:35:52 by cdannapp          #+#    #+#              #
#    Updated: 2015/05/13 18:44:59 by cdannapp         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CFLAGS = -Wall -Werror -Wextra
NAME = ft_computorV1

SRC = 	Parser.cpp \
		Poly.cpp \
		TestStr.cpp \
		main.cpp


SRCO = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME):
	clang++ $(CFLAGS) -c $(SRC)
	clang++ -o $(NAME) $(SRCO)

clean:
	/bin/rm -f $(SRCO)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
