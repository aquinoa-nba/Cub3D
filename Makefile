# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/14 00:12:07 by aquinoa           #+#    #+#              #
#    Updated: 2021/02/18 21:43:41 by aquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS		=	main.c move.c parser.c pars_textures.c pars_floor_n_ceilling.c \
 				validator.c raycast.c raycast_keys.c raycast_utils.c rotation.c \
				sprites.c sprite_utils.c screenshot.c utils.c

OBJS		=	$(SRCS:%.c=%.o)

HEADERS		=	includes/cub.h

# LIBFT		=	libft/libft.a

# LMLX		=	libmlx.dylib

FLAGS		=	-Wall -Wextra -Werror

VPATH		=	srcs


all:			make_libft make_lmlx $(NAME)

make_libft:
				make -C libft bonus

make_lmlx:
				make -C mlx

$(NAME):		$(OBJS) $(HEADERS)
				cp ./mlx/libmlx.dylib ./
				gcc $(FLAGS) $(OBJS) -framework OpenGL -framework AppKit ./libft/libft.a libmlx.dylib -o $@

%.o:			%.c
				gcc -c $< $(FLAGS)

clean:
				make -C libft clean
				rm -f $(OBJS)

fclean:			clean
				make -C libft fclean
				make -C mlx clean
				rm -f $(NAME) libmlx.dylib

re:				fclean all

.PHONY:			all clean fclean re make_lib make_lmlx