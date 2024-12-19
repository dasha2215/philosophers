# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 13:20:57 by dsiroten          #+#    #+#              #
#    Updated: 2024/10/10 19:22:14 by dsiroten         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src
SRC_FILES = main.c init.c args.c simulation.c utils.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:.c=.o)
HEADER = include/philosophers.h

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-g -O0 #-fsanitize=thread
RM = rm -rf

all: $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
