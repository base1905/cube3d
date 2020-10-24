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

SRC = gnl/get_next_line.c gnl/get_next_line_utils.c cub3d.c \
		tools/map_checker.c tools/exit.c tools/init.c tools/raycast.c \
		tools/res_checker.c tools/map_checker.c tools/map_mini.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

HEADER = cub3d.h

OBJ = $(subst .c,.o,$(SRC))

LIBFT = ./libft/libft.a

MINILIBX = ./minilibx/libmlx.a

LIBRARIES = $(LIBFT) $(MINILIBX)

FRAMEWORKS = -framework OpenGL -framework Appkit

all: $(NAME)

#	Automatic Variables
#	$@ 	The file name of the target of the rule. 
#	$<	The name of the first prerequisite.
#	$^	The names of all the prerequisites, with spaces between them.

$(NAME): $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBRARIES) $(FRAMEWORKS)

%.o: %.c $(HEADER) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS)  -c $< -o $@

$(LIBFT):
	@cd libft && make
	@echo "\033[7;32m Libft created \033[0m"
	@echo "\n"

$(MINILIBX):
	@cd minilibx && make
	#@cd mms && cp libmlx.dylib ..
	@echo "\033[7;32m MiniLibX created \033[0m"
	@echo "\n"

clean:
	cd libft && make clean
	@echo "\033[2;32m Libft cleaned \033[0m"
	cd minilibx && make clean
	@echo "\033[2;32m Minilibx cleaned \033[0m"
	rm -f $(OBJ)

fclean: clean
	cd libft && make fclean
	cd minilibx & rm -f libmlx.dylib
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
