/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 17:06:23 by aquinoa           #+#    #+#             */
/*   Updated: 2021/01/30 20:42:33 by aquinoa          ###   ########.fr       */
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
	int			sprite;
	int			floor;
	int			ceilling;
	int			error;
}				t_flags;


typedef struct	s_texture {
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*sprite;
	int			floor;
	int			ceilling;
}				t_texture;

typedef struct	s_map {
	int			x;
	int			y;
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
	char		**map;
	int			map_color;
	t_img		img;
	t_point		point;
	t_plr		plr;
}				t_all;

void			pixel_put(t_img *img, int x, int y, int color);
int				tunnel(t_all *all);
int				tunnel_2(t_all *all);
void			error(int error_num);

#endif
