/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 17:06:23 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/17 22:21:40 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../minilibx_mms_20200219/mlx.h"
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"

# define TYPE "RNSWEFC"

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
}				t_flags;

typedef struct	s_key_flags {
	int			w;
	int			s;
	int			d;
	int			a;
	int			r;
	int			l;
	int			sh;
}				t_key_flags;

typedef struct	s_texture {
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*spr;
	int			fl;
	int			ceil;
}				t_texture;

typedef struct	s_img {
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct	s_raycast {
	double		p_x;
	double		p_y;
	double		p_dir_x;
	double		p_dir_y;
	double		v_cam_x;
	double		v_cam_y;
	double		cam_x;
	double		r_dir_x;
	double		r_dir_y;
	int			r_map_x;
	int			r_map_y;
	double		r_len0_x;
	double		r_len0_y;
	double		r_len_x;
	double		r_len_y;
	double		perp_len;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			wall_height;
	int			wall_top;
	int			wall_bot;
	double		move_speed;
	double		rot_speed;
	double		old_dir_x;
	double		oldv_cam_x;
	double		wall_x;
	int			txr_x;
	int			txr_y;
	int			txr_width;
	int			txr_height;
	double		tex_pos;
	double		scale;
	int			sprts_count;

	double		spr_x;
	double		spr_y;
	double		invDet;
	double		trnfrm_x;
	double		trnfrm_y;
	int			spr_scr_x;
	int			spr_height;
	int			sprite_width;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_end_x;
	int			stripe;
	int			tex_x;
	int			tex_y;
}				t_raycast;

typedef struct	s_sprt {
	double		x;
	double		y;
	double		dist;
}				t_sprt;

typedef struct	s_all {
	void		*mlx;
	void		*win;
	int			res_w;
	int			res_h;
	char		**map;
	int			color;
	char		*line;
	int			sprt_w;
	int			sprt_h;
	t_img		img;
	t_texture	txrs;
	t_flags		cflag;
	t_raycast	rc;
	t_key_flags	flag;
	t_img		txr[4];
}				t_all;

void			parser(char fd, t_list **head, t_all *all);
void			pixel_put(t_img *img, int x, int y, int color);
void			pars_no(t_all *all);
void			pars_so_and_sprt(t_all *all);
void			pars_we(t_all *all);
void			pars_ea(t_all *all);
void			pars_floor_n_ceilling(t_all *all);
int				color_check(char **color);
void			error(char *error);
void			validator(int len, t_all *all);
int				raycast(t_all *all);
int				get_color(t_img *img, int x, int y);
void			sprite_cast(t_all *all, double *perp_buf);
void			scrsht(int fd, t_all *all);

#endif
