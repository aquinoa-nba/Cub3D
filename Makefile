# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/14 00:12:07 by aquinoa           #+#    #+#              #
#    Updated: 2021/02/21 22:17:32 by aquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS		=	main.c move.c parser.c pars_textures.c pars_floor_n_ceilling.c \
 				validator.c raycast.c raycast_keys.c raycast_utils.c rotation.c \
				sprites.c sprite_utils.c screenshot.c utils.c

OBJS		=	$(SRCS:%.c=%.o)

HEADERS		=	includes/cub.h

LIBFT		=	libft/libft.a

LIBMLX		=	libmlx.dylib

LIBMLX_OPGL	=	libmlx.a

FLAGS		=	-Wall -Wextra -Werror

VPATH		=	./srcs


all:			$(NAME)

$(NAME):		$(OBJS)
				make -C libft bonus
				make -C mlx
				make -C minilibx_opengl
				cp ./mlx/$(LIBMLX) ./
				cp ./minilibx_opengl/$(LIBMLX_OPGL) ./
				gcc $(FLAGS) $(OBJS) -framework OpenGL -framework AppKit ./$(LIBFT) ./$(LIBMLX_OPGL) ./$(LIBMLX) -o $@
				@echo cub3D done!

%.o:			%.c $(HEADERS)
				gcc -c $(FLAGS) $< -I ./$(HEADERS)

clean:
				make -C libft clean
				@rm -f $(OBJS)
				@echo objs for cub3D deleted!

fclean:			clean
				make -C libft fclean
				make -C mlx clean
				make -C minilibx_opengl clean
				@rm -f $(NAME) libmlx.dylib libmlx.a
				@echo cub3D deleted!

re:				fclean all

.PHONY:			all clean fclean re make_lib make_lmlx