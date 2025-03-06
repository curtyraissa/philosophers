# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcurty-g <rcurty-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 11:37:29 by rcurty-g          #+#    #+#              #
#    Updated: 2025/03/03 15:27:25 by rcurty-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c init.c utils.c behavior.c \
     actions.c validation.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -pthread $(OBJ) -o $(NAME)
	@echo "Compilation completed successfully!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@echo "Cleanup completed."

fclean: clean
	@rm -rf $(NAME)
	@echo "Everything is clean!"

re: fclean all
	@echo "Recompilation completed successfully!"
