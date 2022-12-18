# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moabid <moabid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 22:50:56 by moabid            #+#    #+#              #
#    Updated: 2022/12/13 23:29:42 by moabid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_V = vector
NAME_M = map

SRCS = main_vector.cpp
SRCS_M = main_map.cpp

OBJS = $(SRCS:.cpp=.o)
OBJS_M = $(SRCS_M:.cpp=.o)

CC = clang++

FLAGS = -Wall -Wextra -Werror

all: $(NAME_V)

map: $(NAME_M)

$(NAME_V): $(OBJS)
	$(CC) $(FLAGS) -I. $(OBJS) -o $(NAME_V)

$(NAME_M): $(OBJS_M)
	$(CC) $(FLAGS) -I. $(OBJS_M) -o $(NAME_M)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_M)

fclean: clean
	rm -f $(NAME_V) $(NAME_M)

re: fclean all

.PHONY: all clean fclean re