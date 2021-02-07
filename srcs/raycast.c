/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:48:56 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/07 23:03:48 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		get_color(t_all *all, int x, int y, int i)
{
	int		color;
	char	*dst;

	dst = all->txr[i].addr + (y * all->txr[i].line_len + x * (all->txr[i].bpp / 8));
	color = *(unsigned int*)dst;
	return (color);
}

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
	if(all->map.map[(int)(all->rc.posX + all->rc.dirY *
			all->rc.moveSpeed)][(int)(all->rc.posY)] != '1')
		all->rc.posX += all->rc.dirY * all->rc.moveSpeed;
	if(all->map.map[(int)(all->rc.posX)][(int)(all->rc.posY -
					all->rc.dirX * all->rc.moveSpeed)] != '1')
		all->rc.posY -= all->rc.dirX * all->rc.moveSpeed;
}

void	move_left(t_all *all)
{
	if(all->map.map[(int)(all->rc.posX - all->rc.dirY *
			all->rc.moveSpeed)][(int)(all->rc.posY)] != '1')
		all->rc.posX -= all->rc.dirY * all->rc.moveSpeed;
	if(all->map.map[(int)(all->rc.posX)][(int)(all->rc.posY +
					all->rc.dirX * all->rc.moveSpeed)] != '1')
		all->rc.posY += all->rc.dirX * all->rc.moveSpeed;
}

void	go(t_all *all)
{
	if(all->map.map[(int)(all->rc.posX + all->rc.dirX *
			all->rc.moveSpeed)][(int)(all->rc.posY)] != '1')
		all->rc.posX += all->rc.dirX * all->rc.moveSpeed;
	if(all->map.map[(int)(all->rc.posX)][(int)(all->rc.posY +
					all->rc.dirY * all->rc.moveSpeed)] != '1')
		all->rc.posY += all->rc.dirY * all->rc.moveSpeed;
}

void	back(t_all *all)
{
	if(all->map.map[(int)(all->rc.posX - all->rc.dirX *
			all->rc.moveSpeed)][(int)(all->rc.posY)] != '1')
		all->rc.posX -= all->rc.dirX * all->rc.moveSpeed;
	if(all->map.map[(int)(all->rc.posX)][(int)(all->rc.posY -
					all->rc.dirY * all->rc.moveSpeed)] != '1')
		all->rc.posY -= all->rc.dirY * all->rc.moveSpeed;
}

void	right(t_all *all)
{
		all->rc.oldDirX = all->rc.dirX;
		all->rc.dirX = all->rc.dirX * cos(-all->rc.rotSpeed) -
							all->rc.dirY * sin(-all->rc.rotSpeed);
		all->rc.dirY = all->rc.oldDirX * sin(-all->rc.rotSpeed) +
								all->rc.dirY * cos(-all->rc.rotSpeed);
		all->rc.oldPlaneX = all->rc.planeX;
		all->rc.planeX = all->rc.planeX * cos(-all->rc.rotSpeed) -
								all->rc.planeY * sin(-all->rc.rotSpeed);
		all->rc.planeY = all->rc.oldPlaneX * sin(-all->rc.rotSpeed) +
								all->rc.planeY * cos(-all->rc.rotSpeed);
}

void	left(t_all *all)
{
	all->rc.oldDirX = all->rc.dirX;
	all->rc.dirX = all->rc.dirX * cos(all->rc.rotSpeed) -
						all->rc.dirY * sin(all->rc.rotSpeed);
	all->rc.dirY = all->rc.oldDirX * sin(all->rc.rotSpeed) +
							all->rc.dirY * cos(all->rc.rotSpeed);
	all->rc.oldPlaneX = all->rc.planeX;
	all->rc.planeX = all->rc.planeX * cos(all->rc.rotSpeed) -
							all->rc.planeY * sin(all->rc.rotSpeed);
	all->rc.planeY = all->rc.oldPlaneX * sin(all->rc.rotSpeed) +
							all->rc.planeY * cos(all->rc.rotSpeed);
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
	all->rc.moveSpeed = all->flag.sh == 1 ? 0.15 : 0.05;
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

void	init_texture(t_all *all)
{
	all->txr[0].img = mlx_xpm_file_to_image(all->mlx, all->map.texture.no, &all->rc.texWidth, &all->rc.texHeight);
	all->txr[0].addr = mlx_get_data_addr(all->txr[0].img, &all->txr[0].bpp, &all->txr[0].line_len, &all->txr[0].endian);
	all->txr[1].img = mlx_xpm_file_to_image(all->mlx, all->map.texture.so, &all->rc.texWidth, &all->rc.texHeight);
	all->txr[1].addr = mlx_get_data_addr(all->txr[1].img, &all->txr[1].bpp, &all->txr[1].line_len, &all->txr[1].endian);
	all->txr[2].img = mlx_xpm_file_to_image(all->mlx, all->map.texture.we, &all->rc.texWidth, &all->rc.texHeight);
	all->txr[2].addr = mlx_get_data_addr(all->txr[2].img, &all->txr[2].bpp, &all->txr[2].line_len, &all->txr[2].endian);
	all->txr[3].img = mlx_xpm_file_to_image(all->mlx, all->map.texture.ea, &all->rc.texWidth, &all->rc.texHeight);
	all->txr[3].addr = mlx_get_data_addr(all->txr[3].img, &all->txr[3].bpp, &all->txr[3].line_len, &all->txr[3].endian);
}

void	get_texture(t_all *all)
{
	if (all->rc.side == 0)
	{
		if (all->rc.stepX > 0)
			all->color = get_color(all, all->rc.texX, all->rc.texY, 0);
		else
			all->color = get_color(all, all->rc.texX, all->rc.texY, 1);
	}
	else
	{
		if (all->rc.stepY > 0)
			all->color = get_color(all, all->rc.texX, all->rc.texY, 2);
		else
			all->color = get_color(all, all->rc.texX, all->rc.texY, 3);
	}
}

int		raycast(t_all *all)
{
	int		x;
	int		y;

	all->img.img = mlx_new_image(all->mlx, all->map.x, all->map.y);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp,
								&all->img.line_len, &all->img.endian);

	init_texture(all);

	move(all);
	x = 0;
	while (x < all->map.x)
	{
		all->rc.cameraX = 2 * x / (double)all->map.x - 1;
		all->rc.rayDirX = all->rc.dirX + all->rc.planeX * all->rc.cameraX;
		all->rc.rayDirY = all->rc.dirY + all->rc.planeY * all->rc.cameraX;

		all->rc.mapX = (int)all->rc.posX;
		all->rc.mapY = (int)all->rc.posY;
		all->rc.deltaDistX = fabs(1 / all->rc.rayDirX);
		all->rc.deltaDistY = fabs(1 / all->rc.rayDirY);
		all->rc.hit = 0;

		if (all->rc.rayDirX < 0)
		{
			all->rc.stepX = -1;
			all->rc.sideDistX = (all->rc.posX - all->rc.mapX) * all->rc.deltaDistX;
		}
		else
		{
			all->rc.stepX = 1;
			all->rc.sideDistX = (all->rc.mapX + 1.0 - all->rc.posX) * all->rc.deltaDistX;
		}
		if (all->rc.rayDirY < 0)
		{
			all->rc.stepY = -1;
			all->rc.sideDistY = (all->rc.posY - all->rc.mapY) * all->rc.deltaDistY;
		}
		else
		{
			all->rc.stepY = 1;
			all->rc.sideDistY = (all->rc.mapY + 1.0 - all->rc.posY) * all->rc.deltaDistY;
		}

		while (all->rc.hit == 0)
		{
			if (all->rc.sideDistX < all->rc.sideDistY)
			{
				all->rc.sideDistX += all->rc.deltaDistX;
				all->rc.mapX += all->rc.stepX;
				all->rc.side = 0;
			}
			else
			{
				all->rc.sideDistY += all->rc.deltaDistY;
				all->rc.mapY += all->rc.stepY;
				all->rc.side = 1;
			}
			if (all->map.map[all->rc.mapX][all->rc.mapY] == '1')
				all->rc.hit = 1;
			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}

		if (all->rc.side == 0)
			all->rc.perpWallDist = (all->rc.mapX - all->rc.posX + (1 - all->rc.stepX) / 2) / all->rc.rayDirX;
		else
			all->rc.perpWallDist = (all->rc.mapY - all->rc.posY + (1 - all->rc.stepY) / 2) / all->rc.rayDirY;

		all->rc.lineHeight = (int)(all->map.y / all->rc.perpWallDist);
		all->rc.drawStart = -all->rc.lineHeight / 2 + all->map.y / 2;
		if (all->rc.drawStart < 0)
			all->rc.drawStart = 0;
		all->rc.drawEnd = all->rc.lineHeight / 2 + all->map.y / 2;
		if (all->rc.drawEnd >= all->map.y)
			all->rc.drawEnd = all->map.y - 1;

		if (all->rc.side == 0)
			all->rc.wallX = all->rc.posY + all->rc.perpWallDist * all->rc.rayDirY;
		else
			all->rc.wallX = all->rc.posX + all->rc.perpWallDist * all->rc.rayDirX;
		all->rc.wallX -= floor((all->rc.wallX));
		all->rc.texX = (int)(all->rc.wallX * (double)(all->rc.texWidth));
		all->rc.texX = all->rc.texWidth - all->rc.texX - 1;

		all->rc.step = 1.0 * all->rc.texHeight / all->rc.lineHeight;
		all->rc.texPos = (all->rc.drawStart - all->map.y / 2 + all->rc.lineHeight / 2) * all->rc.step;

		y = 0;
		while (y < all->map.y)
		{
			if (y < all->rc.drawStart)
				pixel_put(&all->img, x, y, all->map.texture.ceil);
			else if (y >= all->rc.drawStart && y <= all->rc.drawEnd)
			{
				all->rc.texY = (int)all->rc.texPos & (all->rc.texHeight - 1);
				all->rc.texPos += all->rc.step;
				get_texture(all);
				pixel_put(&all->img, x, y, all->color);
			}
			if (y > all->rc.drawEnd && y < all->map.y)
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
