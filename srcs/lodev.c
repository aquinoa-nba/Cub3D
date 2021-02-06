/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lodev.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:48:56 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/06 22:05:46 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int		close_window(int keycode, t_all *all)
{
	exit(0);
}

void	move_right(t_all *all)
{
	if(all->map.map[(int)(all->lodev.posX + all->lodev.dirY * all->lodev.moveSpeed)][(int)(all->lodev.posY)] != '1')
		all->lodev.posX += all->lodev.dirY * all->lodev.moveSpeed;
	if(all->map.map[(int)(all->lodev.posX)][(int)(all->lodev.posY - all->lodev.dirX * all->lodev.moveSpeed)] != '1')
		all->lodev.posY -= all->lodev.dirX * all->lodev.moveSpeed;
}

void	move_left(t_all *all)
{
	if(all->map.map[(int)(all->lodev.posX - all->lodev.dirY * all->lodev.moveSpeed)][(int)(all->lodev.posY)] != '1')
		all->lodev.posX -= all->lodev.dirY * all->lodev.moveSpeed;
	if(all->map.map[(int)(all->lodev.posX)][(int)(all->lodev.posY + all->lodev.dirX * all->lodev.moveSpeed)] != '1')
		all->lodev.posY += all->lodev.dirX * all->lodev.moveSpeed;
}

void	go(t_all *all)
{
	if(all->map.map[(int)(all->lodev.posX + all->lodev.dirX * all->lodev.moveSpeed)][(int)(all->lodev.posY)] != '1')
		all->lodev.posX += all->lodev.dirX * all->lodev.moveSpeed;
	if(all->map.map[(int)(all->lodev.posX)][(int)(all->lodev.posY + all->lodev.dirY * all->lodev.moveSpeed)] != '1')
		all->lodev.posY += all->lodev.dirY * all->lodev.moveSpeed;
}

void	back(t_all *all)
{
	if(all->map.map[(int)(all->lodev.posX - all->lodev.dirX * all->lodev.moveSpeed)][(int)(all->lodev.posY)] != '1')
		all->lodev.posX -= all->lodev.dirX * all->lodev.moveSpeed;
	if(all->map.map[(int)(all->lodev.posX)][(int)(all->lodev.posY - all->lodev.dirY * all->lodev.moveSpeed)] != '1')
		all->lodev.posY -= all->lodev.dirY * all->lodev.moveSpeed;
}

void	right(t_all *all)
{
		all->lodev.oldDirX = all->lodev.dirX;
		all->lodev.dirX = all->lodev.dirX * cos(-all->lodev.rotSpeed) - all->lodev.dirY * sin(-all->lodev.rotSpeed);
		all->lodev.dirY = all->lodev.oldDirX * sin(-all->lodev.rotSpeed) + all->lodev.dirY * cos(-all->lodev.rotSpeed);
		all->lodev.oldPlaneX = all->lodev.planeX;
		all->lodev.planeX = all->lodev.planeX * cos(-all->lodev.rotSpeed) - all->lodev.planeY * sin(-all->lodev.rotSpeed);
		all->lodev.planeY = all->lodev.oldPlaneX * sin(-all->lodev.rotSpeed) + all->lodev.planeY * cos(-all->lodev.rotSpeed);
}

void	left(t_all *all)
{
	all->lodev.oldDirX = all->lodev.dirX;
	all->lodev.dirX = all->lodev.dirX * cos(all->lodev.rotSpeed) - all->lodev.dirY * sin(all->lodev.rotSpeed);
	all->lodev.dirY = all->lodev.oldDirX * sin(all->lodev.rotSpeed) + all->lodev.dirY * cos(all->lodev.rotSpeed);
	all->lodev.oldPlaneX = all->lodev.planeX;
	all->lodev.planeX = all->lodev.planeX * cos(all->lodev.rotSpeed) - all->lodev.planeY * sin(all->lodev.rotSpeed);
	all->lodev.planeY = all->lodev.oldPlaneX * sin(all->lodev.rotSpeed) + all->lodev.planeY * cos(all->lodev.rotSpeed);
}

void	speed(t_all *all)
{
	int	i;

	all->lodev.moveSpeed = 0.25;
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
	all->lodev.moveSpeed = all->flag.sh == 1 ? 0.15 : 0.05;
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
	// ft_putnbr_fd(keycode, 1);
	return (1);
}

int		lodev(t_all *all)
{
	int		color;
	int		x;
	int		y;

	color = all->map.texture.fl;

	all->img.img = mlx_new_image(all->mlx, all->map.x, all->map.y);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp,
								&all->img.line_len, &all->img.endian);

	move(all);
	x = 0;
	while (x < all->map.x)
	{
		all->lodev.cameraX = 2 * x / (double)all->map.x - 1;
		all->lodev.rayDirX = all->lodev.dirX + all->lodev.planeX * all->lodev.cameraX;
		all->lodev.rayDirY = all->lodev.dirY + all->lodev.planeY * all->lodev.cameraX;

		all->lodev.mapX = (int)all->lodev.posX;
		all->lodev.mapY = (int)all->lodev.posY;
		all->lodev.deltaDistX = fabs(1 / all->lodev.rayDirX);
		all->lodev.deltaDistY = fabs(1 / all->lodev.rayDirY);
		all->lodev.hit = 0;

		if (all->lodev.rayDirX < 0)
		{
			all->lodev.stepX = -1;
			all->lodev.sideDistX = (all->lodev.posX - all->lodev.mapX) * all->lodev.deltaDistX;
		}
		else
		{
			all->lodev.stepX = 1;
			all->lodev.sideDistX = (all->lodev.mapX + 1.0 - all->lodev.posX) * all->lodev.deltaDistX;
		}
		if (all->lodev.rayDirY < 0)
		{
			all->lodev.stepY = -1;
			all->lodev.sideDistY = (all->lodev.posY - all->lodev.mapY) * all->lodev.deltaDistY;
		}
		else
		{
			all->lodev.stepY = 1;
			all->lodev.sideDistY = (all->lodev.mapY + 1.0 - all->lodev.posY) * all->lodev.deltaDistY;
		}

		while (all->lodev.hit == 0)
		{
			if (all->lodev.sideDistX < all->lodev.sideDistY)
			{
				all->lodev.sideDistX += all->lodev.deltaDistX;
				all->lodev.mapX += all->lodev.stepX;
				all->lodev.side = 0;
			}
			else
			{
				all->lodev.sideDistY += all->lodev.deltaDistY;
				all->lodev.mapY += all->lodev.stepY;
				all->lodev.side = 1;
			}
			if (all->map.map[all->lodev.mapX][all->lodev.mapY] == '1')
				all->lodev.hit = 1;
			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}

		if (all->lodev.side == 0)
			all->lodev.perpWallDist = (all->lodev.mapX - all->lodev.posX + (1 - all->lodev.stepX) / 2) / all->lodev.rayDirX;
		else
			all->lodev.perpWallDist = (all->lodev.mapY - all->lodev.posY + (1 - all->lodev.stepY) / 2) / all->lodev.rayDirY;

		all->lodev.lineHeight = (int)(all->map.y / all->lodev.perpWallDist);
		all->lodev.drawStart = -all->lodev.lineHeight / 2 + all->map.y / 2;
		if (all->lodev.drawStart < 0)
			all->lodev.drawStart = 0;
		all->lodev.drawEnd = all->lodev.lineHeight / 2 + all->map.y / 2;
		if (all->lodev.drawEnd >= all->map.y)
			all->lodev.drawEnd = all->map.y - 1;

		if (all->lodev.side == 0)
		{
			if (all->lodev.stepX > 0)
				color = 0xFFA07A;
			else
				color = 0xFA8072;
		}
		else
		{
			if (all->lodev.stepY > 0)
				color = 0xCD5C5C;
			else
				color = 0xF08080;
		}

		y = 0;
		while (y < all->map.y)
		{
			if (y < all->lodev.drawStart)
				pixel_put(&all->img, x, y, all->map.texture.ceil);
			else if (y >= all->lodev.drawStart && y <= all->lodev.drawEnd)
				pixel_put(&all->img, x, y, color);
			if (y > all->lodev.drawEnd && y < all->map.y)
				pixel_put(&all->img, x, y, all->map.texture.fl);
			y++;
		}
		x++;
	}

	mlx_hook(all->win, 2, (1L<<0), key_press, all);
	mlx_hook(all->win, 3, (1L<<0), key_unpress, all);
    mlx_hook(all->win, 17, (1L<<0),	close_window, all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	mlx_string_put(all->mlx, all->win, all->map.x / 2, all->map.y / 2, 0xffffff, "+");
	mlx_destroy_image(all->mlx, all->img.img);
	return (0);
}
