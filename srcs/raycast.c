/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:48:56 by aquinoa           #+#    #+#             */
/*   Updated: 2021/03/13 17:20:09 by aquinoa          ###   ########.fr       */
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

void	get_texture(t_all *all)
{
	if (all->rc.side == 0)
	{
		if (all->rc.step_x > 0)
		{
			all->rc.txr_width = all->rc.res[1].txr_width;
			all->rc.txr_height = all->rc.res[1].txr_height;
			all->color = get_color(&all->txr[1], all->rc.txr_x, all->rc.txr_y);
		}
		else
		{
			all->rc.txr_width = all->rc.res[0].txr_width;
			all->rc.txr_height = all->rc.res[0].txr_height;
			all->color = get_color(&all->txr[0], all->rc.txr_x, all->rc.txr_y);
		}
	}
	else
	{
		if (all->rc.step_y > 0)
		{
			all->color = get_color(&all->txr[3], all->rc.txr_x, all->rc.txr_y);
			all->rc.txr_width = all->rc.res[3].txr_width;
			all->rc.txr_height = all->rc.res[3].txr_height;
		}
		else
		{
			all->rc.txr_width = all->rc.res[2].txr_width;
			all->rc.txr_height = all->rc.res[2].txr_height;
			all->color = get_color(&all->txr[2], all->rc.txr_x, all->rc.txr_y);
		}
	}
}

void	draw(int x, t_all *all)
{
	int		y;

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
}

int		raycast(t_all *all)
{
	int		x;
	double	perp_buf[all->res_w];

	all->img.img = mlx_new_image(all->mlx, all->res_w, all->res_h);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp,
								&all->img.line_len, &all->img.endian);
	move(all);
	x = -1;
	while (++x < all->res_w)
	{
		all->rc.cam_x = 2 * x / (double)all->res_w - 1;
		ray_dir_n_dist(all);
		draw(x, all);
		perp_buf[x] = all->rc.perp_len;
	}
	sprites(all, perp_buf);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	mlx_string_put(all->mlx, all->win, all->res_w / 2,
										all->res_h / 2, 0xffffff, "+");
	mlx_destroy_image(all->mlx, all->img.img);
	return (0);
}
