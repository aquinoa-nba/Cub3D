/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 17:06:23 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/05 21:19:50 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../minilibx_opengl_20191021/mlx.h"
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"

#define SCALE 10

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

typedef struct	s_lodev {
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;

	double	cameraX;
	double	rayDirX;
	double	rayDirY;

	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;

	int		lineHeight;
	int		drawStart;
	int		drawEnd;

	double	moveSpeed;
	double	rotSpeed;

	double	oldDirX;
	double	oldDirY;
	double	oldPlaneX;
}				t_lodev;


typedef struct	s_all {
	void		*mlx;
	void		*win;
	t_img		img;
	t_point		point;
	t_plr		plr;
	t_map		map;
	t_lodev		lodev;
}				t_all;

void			pixel_put(t_img *img, int x, int y, int color);
void			error(char *error);
void			parser(char fd, t_list **head, t_all *all);
void			validator(int len, t_all *all);
void			make_window(t_all *all);
int				lodev(t_all *all);

#endif
