# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arannara <base1905@yandex.ru>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/05 12:37:48 by arannara          #+#    #+#              #
#    Updated: 2020/10/05 12:38:40 by arannara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = cub3d.c

HEADER = cub3d.h	

OBJ = $(subst .c,.o,$(SRC))

LIBFT = ./libft/libft.a

MINILIBX = ./minilibx/libmlx.a

all: $(NAME)

$(NAME): $(OBJ) 
	gcc -o $@ $^ -Wall -Wextra -Werror -L ./libft/ -lft

%.o: %.c $(HEADER) $(LIBFT)
	gcc -Wall -Wextra -Werror -c $< -o $@

$(LIBFT):
	@echo "LIBFT BUILDS"
	@make -C ./libft/
	@echo "LIBFT DONE"

clean:
	@make clean -C ./libft/
	@rm -f $(OBJ)

fclean: clean
	@make clean -C ./libft/
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
