/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:48:56 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/17 22:21:43 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		get_color(t_img *img, int x, int y)
{
	int		color;
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int		close_window(t_all *all)
{
	mlx_destroy_image(all->mlx, all->img.img);
	mlx_destroy_window(all->mlx, all->win);
	exit(0);
}

void	move_right(t_all *all)
{
	if(all->map[(int)(all->rc.p_x + all->rc.v_cam_x *
			all->rc.move_speed)][(int)(all->rc.p_y)] == '0')
		all->rc.p_x += all->rc.v_cam_x * all->rc.move_speed;
	if(all->map[(int)(all->rc.p_x)][(int)(all->rc.p_y +
					all->rc.v_cam_y * all->rc.move_speed)] == '0')
		all->rc.p_y += all->rc.v_cam_y * all->rc.move_speed;
}

void	move_left(t_all *all)
{
	if(all->map[(int)(all->rc.p_x - all->rc.v_cam_x *
			all->rc.move_speed)][(int)(all->rc.p_y)] == '0')
		all->rc.p_x -= all->rc.v_cam_x * all->rc.move_speed;
	if(all->map[(int)(all->rc.p_x)][(int)(all->rc.p_y -
					all->rc.v_cam_y * all->rc.move_speed)] == '0')
		all->rc.p_y -= all->rc.v_cam_y * all->rc.move_speed;
}

void	go(t_all *all)
{
	if(all->map[(int)(all->rc.p_x - (all->rc.v_cam_y) *
			all->rc.move_speed)][(int)(all->rc.p_y)] == '0')
		all->rc.p_x -= all->rc.v_cam_y * all->rc.move_speed;
	if(all->map[(int)(all->rc.p_x)][(int)(all->rc.p_y +
					(all->rc.v_cam_x) * all->rc.move_speed)] == '0')
		all->rc.p_y += all->rc.v_cam_x * all->rc.move_speed;
}

void	back(t_all *all)
{
	if(all->map[(int)(all->rc.p_x + (all->rc.v_cam_y) *
			all->rc.move_speed)][(int)(all->rc.p_y)] == '0')
		all->rc.p_x += all->rc.v_cam_y * all->rc.move_speed;
	if(all->map[(int)(all->rc.p_x)][(int)(all->rc.p_y -
					(all->rc.v_cam_x) * all->rc.move_speed)] == '0')
		all->rc.p_y -= all->rc.v_cam_x * all->rc.move_speed;
}

void	right(t_all *all)
{
		all->rc.old_dir_x = all->rc.p_dir_x;
		all->rc.p_dir_x = all->rc.p_dir_x * cos(-all->rc.rot_speed) -
							all->rc.p_dir_y * sin(-all->rc.rot_speed);
		all->rc.p_dir_y = all->rc.old_dir_x * sin(-all->rc.rot_speed) +
								all->rc.p_dir_y * cos(-all->rc.rot_speed);
		all->rc.oldv_cam_x = all->rc.v_cam_x;
		all->rc.v_cam_x = all->rc.v_cam_x * cos(-all->rc.rot_speed) -
								all->rc.v_cam_y * sin(-all->rc.rot_speed);
		all->rc.v_cam_y = all->rc.oldv_cam_x * sin(-all->rc.rot_speed) +
								all->rc.v_cam_y * cos(-all->rc.rot_speed);
}

void	left(t_all *all)
{
	all->rc.old_dir_x = all->rc.p_dir_x;
	all->rc.p_dir_x = all->rc.p_dir_x * cos(all->rc.rot_speed) -
						all->rc.p_dir_y * sin(all->rc.rot_speed);
	all->rc.p_dir_y = all->rc.old_dir_x * sin(all->rc.rot_speed) +
							all->rc.p_dir_y * cos(all->rc.rot_speed);
	all->rc.oldv_cam_x = all->rc.v_cam_x;
	all->rc.v_cam_x = all->rc.v_cam_x * cos(all->rc.rot_speed) -
							all->rc.v_cam_y * sin(all->rc.rot_speed);
	all->rc.v_cam_y = all->rc.oldv_cam_x * sin(all->rc.rot_speed) +
							all->rc.v_cam_y * cos(all->rc.rot_speed);
}

int		key_unpress(int keycode, t_all *all)
{
    if (keycode == 13)
		all->flag.w = 0;
    if (keycode == 1)
		all->flag.s = 0;
    if (keycode == 2)
		all->flag.d = 0;
    if (keycode == 0)
		all->flag.a = 0;
    if (keycode == 257)
		all->flag.sh = 0;
    if (keycode == 123 || keycode == 12)
		all->flag.l = 0;
    if (keycode == 124 || keycode == 14)
		all->flag.r = 0;
	return (1);
}

void	move(t_all *all)
{
	all->flag.w == 1 ? go(all) : 0;
	all->flag.s == 1 ? back(all) : 0;
	all->flag.d == 1 ? move_right(all) : 0;
	all->flag.a == 1 ? move_left(all) : 0;
	all->rc.move_speed = all->flag.sh == 1 ? 0.5 : 0.05;
	all->flag.r == 1 ? right(all) : 0;
	all->flag.l == 1 ? left(all) : 0;
}

int		key_press(int keycode, t_all *all)
{
	if (keycode == 53)
	{
		mlx_destroy_window(all->mlx, all->win);
		exit(0);
	}
    if (keycode == 13)
		all->flag.w = 1;
    if (keycode == 1)
		all->flag.s = 1;
    if (keycode == 2)
		all->flag.d = 1;
    if (keycode == 0)
		all->flag.a = 1;
	if (keycode == 123 || keycode == 12)
		all->flag.l = 1;
	if (keycode == 124 || keycode == 14)
		all->flag.r = 1;
	if (keycode == 257)
		all->flag.sh = 1;
	return (1);
}

void	get_texture(t_all *all)
{
	if (all->rc.side == 0)
	{
		if (all->rc.step_x > 0)
			all->color = get_color(&all->txr[0], all->rc.txr_x, all->rc.txr_y);
		else
			all->color = get_color(&all->txr[1], all->rc.txr_x, all->rc.txr_y);
	}
	else
	{
		if (all->rc.step_y > 0)
			all->color = get_color(&all->txr[2], all->rc.txr_x, all->rc.txr_y);
		else
			all->color = get_color(&all->txr[3], all->rc.txr_x, all->rc.txr_y);
	}
}

int		raycast(t_all *all)
{
	int		x;
	int		y;
	double perp_buf[all->res_w];

	all->img.img = mlx_new_image(all->mlx, all->res_w, all->res_h);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp,
								&all->img.line_len, &all->img.endian);

	move(all);
	x = 0;
	while (x < all->res_w)
	{
		all->rc.cam_x = 2 * x / (double)all->res_w - 1;
		all->rc.r_dir_x = all->rc.p_dir_x + all->rc.v_cam_x * all->rc.cam_x;
		all->rc.r_dir_y = all->rc.p_dir_y + all->rc.v_cam_y * all->rc.cam_x;

		all->rc.r_map_x = (int)all->rc.p_x;
		all->rc.r_map_y = (int)all->rc.p_y;
		all->rc.r_len_x = fabs(1 / all->rc.r_dir_x);
		all->rc.r_len_y = fabs(1 / all->rc.r_dir_y);
		all->rc.hit = 0;

		if (all->rc.r_dir_x < 0)
		{
			all->rc.step_x = -1;
			all->rc.r_len0_x = (all->rc.p_x - all->rc.r_map_x) * all->rc.r_len_x;
		}
		else
		{
			all->rc.step_x = 1;
			all->rc.r_len0_x = (all->rc.r_map_x + 1.0 - all->rc.p_x) * all->rc.r_len_x;
		}
		if (all->rc.r_dir_y < 0)
		{
			all->rc.step_y = -1;
			all->rc.r_len0_y = (all->rc.p_y - all->rc.r_map_y) * all->rc.r_len_y;
		}
		else
		{
			all->rc.step_y = 1;
			all->rc.r_len0_y = (all->rc.r_map_y + 1.0 - all->rc.p_y) * all->rc.r_len_y;
		}

		while (all->rc.hit == 0)
		{
			if (all->rc.r_len0_x < all->rc.r_len0_y)
			{
				all->rc.r_len0_x += all->rc.r_len_x;
				all->rc.r_map_x += all->rc.step_x;
				all->rc.side = 0;
			}
			else
			{
				all->rc.r_len0_y += all->rc.r_len_y;
				all->rc.r_map_y += all->rc.step_y;
				all->rc.side = 1;
			}
			if (all->map[all->rc.r_map_x][all->rc.r_map_y] == '1')
				all->rc.hit = 1;
			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}

		if (all->rc.side == 0)
			all->rc.perp_len = (all->rc.r_map_x - all->rc.p_x + (1 - all->rc.step_x) / 2) / all->rc.r_dir_x;
		else
			all->rc.perp_len = (all->rc.r_map_y - all->rc.p_y + (1 - all->rc.step_y) / 2) / all->rc.r_dir_y;

		all->rc.wall_height = (int)(all->res_h / all->rc.perp_len);
		all->rc.wall_top = -all->rc.wall_height / 2 + all->res_h / 2;
		if (all->rc.wall_top < 0)
			all->rc.wall_top = 0;
		all->rc.wall_bot = all->rc.wall_height / 2 + all->res_h / 2;
		if (all->rc.wall_bot >= all->res_h)
			all->rc.wall_bot = all->res_h - 1;

		if (all->rc.side == 0)
			all->rc.wall_x = all->rc.p_y + all->rc.perp_len * all->rc.r_dir_y;
		else
			all->rc.wall_x = all->rc.p_x + all->rc.perp_len * all->rc.r_dir_x;
		all->rc.wall_x -= floor((all->rc.wall_x));
		all->rc.txr_x = (int)(all->rc.wall_x * (double)(all->rc.txr_width));
		all->rc.txr_x = all->rc.txr_width - all->rc.txr_x - 1;

		all->rc.scale = 1.0 * all->rc.txr_height / all->rc.wall_height;
		all->rc.tex_pos = (all->rc.wall_top - all->res_h / 2 + all->rc.wall_height / 2) * all->rc.scale; //!!!!!!

		y = 0;
		while (y < all->res_h)
		{
			if (y < all->rc.wall_top)
				pixel_put(&all->img, x, y, all->txrs.ceil);
			else if (y >= all->rc.wall_top && y <= all->rc.wall_bot)
			{
				all->rc.txr_y = (int)all->rc.tex_pos & (all->rc.txr_height - 1);
				all->rc.tex_pos += all->rc.scale;
				get_texture(all);
				pixel_put(&all->img, x, y, all->color);
			}
			if (y > all->rc.wall_bot && y < all->res_h)
				pixel_put(&all->img, x, y, all->txrs.fl);
			y++;
		}
		perp_buf[x] = all->rc.perp_len;
		x++;
	}

	mlx_hook(all->win, 2, (1L<<0), key_press, all);
	mlx_hook(all->win, 3, (1L<<0), key_unpress, all);
    mlx_hook(all->win, 17, (1L<<0),	close_window, all);
	sprite_cast(all, perp_buf);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	mlx_string_put(all->mlx, all->win, all->res_w / 2, all->res_h / 2, 0xffffff, "+");
	mlx_destroy_image(all->mlx, all->img.img);
	return (0);
}
