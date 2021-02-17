# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/14 00:12:07 by aquinoa           #+#    #+#              #
#    Updated: 2021/02/16 15:07:38 by aquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS		=	main.c parser.c pars_textures.c pars_floor_n_ceilling.c validator.c \
				raycast.c sprites.c screenshot.c utils.c

OBJS		=	$(SRCS:%.c=%.o)

# HEADERS		=	includes/cub.h

FLAGS		=	-Wall -Wextra -Werror

VPATH		=	srcs

$(NAME):		$(OBJS)
				make -C libft bonus
				gcc $(FLAGS) -L. -lmlx $(OBJS) -framework opengl -framework appkit ./libft/libft.a -o $@

all:			$(NAME)

%.o:			%.c
				gcc $(FLAGS) -c $<

clean:
				make -C libft clean
				rm -f $(OBJS)

fclean:			clean
				make -C libft fclean
				rm -f $(NAME)

re:				fclean all

.PHONY:		all clean fclean re