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

SRC = gnl/get_next_line.c gnl/get_next_line_utils.c cub3d.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror

# 	‘-I dir’
#	‘--include-dir=dir’
#	Specifies a directory dir to search for included makefiles.

HEADER = cub3d.h	

OBJ = $(subst .c,.o,$(SRC))

LIBFT = ./libft/libft.a

MINILIBX = ./minilibx/libmlx.a

FRAMEWORKS = -framework OpenGL -framework Appkit

all: $(NAME)

#	Automatic Variables
#	$@ 	The file name of the target of the rule. 
#	$<	The name of the first prerequisite.
#	$^	The names of all the prerequisites, with spaces between them.

$(NAME): $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) -L ./libft -lft

%.o: %.c $(HEADER) $(LIBFT)
	$(CC) $(CFLAGS) -c $< -o $@

 $(LIBFT):
	@make -C ./libft
	@echo "Libft Created"
	@echo "\n"

# make -C 	‘-C dir’ 
# 			‘--directory=dir’ Change to directory dir before reading the makefiles.

clean:
	make clean -C ./libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
