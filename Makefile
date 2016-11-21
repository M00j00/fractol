# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amanchon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/29 04:25:44 by amanchon          #+#    #+#              #
#    Updated: 2016/11/21 06:31:49 by amanchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol
FLAGS	=	-Wall -Wextra -Werror
LIB		=	-L./includes -lft -lmlx -framework OpenGL -framework AppKit
CC		=	gcc
SRC		=	main.c fractal.c display.c hook.c image.c
OBJ		=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):
	$(MAKE) -C libft
	@mkdir includes
	@cp libft/libft.a ./includes/
	@cp libft/libft.h ./includes/
	@cp /usr/local/lib/libmlx.a ./includes/
	@cp /usr/local/include/mlx.h ./includes/
	$(CC) $(FLAGS) $(LIB) $(SRC) -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $^ -o $@
	echo "."

clean:
	$(MAKE) -C libft/ clean
	@rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft/ fclean
	@rm -rf includes/
	rm -f $(NAME)

re: fclean all
