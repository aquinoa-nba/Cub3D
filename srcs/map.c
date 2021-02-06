/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:15:22 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/06 19:27:22 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

// void	pixel_put(t_img *img, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
// 	*(unsigned int*)dst = color;
// }

void	scale_map(t_all all)
{
	int end_x;
	int end_y;

	end_x = (all.point.x + 1) * SCALE;
	end_y = (all.point.y + 1) * SCALE;
	all.point.x *= SCALE;
	all.point.y *= SCALE;
	while (all.point.y < end_y)
	{
		while (all.point.x < end_x)
		{
			pixel_put(&all.img, all.point.x, all.point.y, 0xffffff);
			all.point.x++;
		}
		all.point.x -= SCALE;
		all.point.y++;
	}
}

void	ft_cast_ray(t_all *all)
{
	t_plr	ray;
	int		len;

	len = 0;
	ray = all->plr;
	ray.start = ray.dir - M_PI / 6;
	ray.end = ray.dir + M_PI / 6;
	while (ray.start <= ray.end)
	{
		ray.x = all->plr.x;
		ray.y = all->plr.y;
		while (all->map.map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
		{
			ray.x += cos(ray.start);
			ray.y += sin(ray.start);
			pixel_put(&all->img, ray.x, ray.y, all->plr.color);
			len++;
		}
		ray.start += (M_PI / 3) / all->map.x;
	}
}

void	draw_mini_map(t_all *all)
{
	all->point.x = 0;
	all->point.y = 0;
	all->img.img = mlx_new_image(all->mlx, all->map.x, all->map.y);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp,
								&all->img.line_len, &all->img.endian);
	while (all->map.map[all->point.y])
	{
		all->point.x = 0;
		while (all->map.map[all->point.y][all->point.x])
		{
			if (all->map.map[all->point.y][all->point.x] == '1')
				scale_map(*all);
			all->point.x++;
		}
		all->point.y++;
		ft_cast_ray(all);
	}
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
}

// int		key_press(int keycode, t_all *all)
// {
// 	if (keycode == 53)
// 	{
// 		mlx_destroy_window(all->mlx, all->win);
// 		exit(0);
// 	}
// 	if (keycode == 13)
// 	{
// 		all->plr.x += cos(all->plr.dir) * 3;
// 		all->plr.y += sin(all->plr.dir) * 3;
// 	}
// 	if (keycode == 1)
// 	{
// 		all->plr.x -= cos(all->plr.dir) * 3;
// 		all->plr.y -= sin(all->plr.dir) * 3;
// 	}
// 	if (keycode == 0)
// 		all->plr.dir -= 0.1;
// 	if (keycode == 2)
// 		all->plr.dir += 0.1;
// 	draw_mini_map(all);
// 	return (0);
// }

// int		close_window(int keycode, t_all *all)
// {
// 	exit(0);
// }

// int		player(t_all *all)
// {
// 	int		i;
// 	int		j;

// 	i = -1;
// 	while (all->map.map[++i])
// 	{
// 		j = -1;
// 		while (all->map.map[i][++j])
// 		{
// 			if (all->map.map[i][j] == 'N' || all->map.map[i][j] == 'S' ||
// 				all->map.map[i][j] == 'W' || all->map.map[i][j] == 'E')
// 			{
// 				all->plr.x = j * SCALE;
// 				all->plr.y = i * SCALE;
// 				if (all->map.map[i][j] == 'N')
// 					all->plr.dir = 3 * M_PI_2;
// 				else if (all->map.map[i][j] == 'S')
// 					all->plr.dir = M_PI_2;
// 				else if (all->map.map[i][j] == 'W')
// 					all->plr.dir = M_PI;
// 				else
// 					all->plr.dir = 2 * M_PI;
// 				return (1);
// 			}
// 		}
// 	}
// 	return (0);
// }

// void	make_window(t_all *all)
// {
// 	player(all);
// 	all->mlx = mlx_init();
// 	all->win = mlx_new_window(all->mlx, all->map.x, all->map.y, "figures");
// 	draw_mini_map(all);
// 	mlx_hook(all->win, 2, (1L << 0), key_press, all);
// 	mlx_hook(all->win, 17, (1L << 0), close_window, all);
// 	mlx_loop(all->mlx);
// }
