/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 17:06:23 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/03 15:32:21 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../minilibx_opengl_20191021/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"

typedef struct	s_flags
{
	int			r;
	int			no;
	int			so;
	int			we;
	int			ea;
	int			spr;
	int			fl;
	int			ceil;
	int			error;
}				t_flags;


typedef struct	s_texture {
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*spr;
	int			fl;
	int			ceil;
}				t_texture;

typedef struct	s_map {
	char		*line;
	char		**map;
	char		**sline;
	int			x;
	int			y;
	char		**f;
	char		**c;
	t_texture	texture;
	t_flags		flags;
}				t_map;

typedef struct	s_img {
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct	s_point {
	int			x;
	int			y;
}				t_point;

typedef struct	s_player {
	float		x;
	float		y;
	float		dir;
	float		start;
	float		end;
	int			color;
}				t_plr;

typedef struct	s_all {
	void		*mlx;
	void		*win;
	// char		**map;
	int			map_color;
	t_img		img;
	t_point		point;
	t_plr		plr;
	t_map		map;
}				t_all;

void			pixel_put(t_img *img, int x, int y, int color);
int				tunnel(t_all *all);
int				tunnel_2(t_all *all);
void			error(char *error);
void			parser(char fd, t_list **head, t_all *all);
void			validator(int len, t_all *all);

#endif
