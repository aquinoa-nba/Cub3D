/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lodev.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:48:56 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/05 22:35:22 by aquinoa          ###   ########.fr       */
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

int		key_press(int keycode, t_all *all)
{
	//move forward if no wall in front of you
    if (keycode == 13)
    {
      if(all->map.map[(int)(all->lodev.posX + all->lodev.dirX * all->lodev.moveSpeed)][(int)(all->lodev.posY)] != '1') all->lodev.posX += all->lodev.dirX * all->lodev.moveSpeed;
      if(all->map.map[(int)(all->lodev.posX)][(int)(all->lodev.posY + all->lodev.dirY * all->lodev.moveSpeed)] != '1') all->lodev.posY += all->lodev.dirY * all->lodev.moveSpeed;
    }
    //move backwards if no wall behind you
    if (keycode == 1)
    {
      if(all->map.map[(int)(all->lodev.posX - all->lodev.dirX * all->lodev.moveSpeed)][(int)(all->lodev.posY)] != '1') all->lodev.posX -= all->lodev.dirX * all->lodev.moveSpeed;
      if(all->map.map[(int)(all->lodev.posX)][(int)(all->lodev.posY - all->lodev.dirY * all->lodev.moveSpeed)] != '1') all->lodev.posY -= all->lodev.dirY * all->lodev.moveSpeed;
    }
    //rotate to the right
    if (keycode == 2)
    {
      //both camera direction and camera plane must be rotated
      all->lodev.oldDirX = all->lodev.dirX;
      all->lodev.dirX = all->lodev.dirX * cos(-all->lodev.rotSpeed) - all->lodev.dirY * sin(-all->lodev.rotSpeed);
      all->lodev.dirY = all->lodev.oldDirX * sin(-all->lodev.rotSpeed) + all->lodev.dirY * cos(-all->lodev.rotSpeed);
      all->lodev.oldPlaneX = all->lodev.planeX;
      all->lodev.planeX = all->lodev.planeX * cos(-all->lodev.rotSpeed) - all->lodev.planeY * sin(-all->lodev.rotSpeed);
      all->lodev.planeY = all->lodev.oldPlaneX * sin(-all->lodev.rotSpeed) + all->lodev.planeY * cos(-all->lodev.rotSpeed);
    }
    //rotate to the left
    if (keycode == 0)
    {
      //both camera direction and camera plane must be rotated
      all->lodev.oldDirX = all->lodev.dirX;
      all->lodev.dirX = all->lodev.dirX * cos(all->lodev.rotSpeed) - all->lodev.dirY * sin(all->lodev.rotSpeed);
      all->lodev.dirY = all->lodev.oldDirX * sin(all->lodev.rotSpeed) + all->lodev.dirY * cos(all->lodev.rotSpeed);
      all->lodev.oldPlaneX = all->lodev.planeX;
      all->lodev.planeX = all->lodev.planeX * cos(all->lodev.rotSpeed) - all->lodev.planeY * sin(all->lodev.rotSpeed);
      all->lodev.planeY = all->lodev.oldPlaneX * sin(all->lodev.rotSpeed) + all->lodev.planeY * cos(all->lodev.rotSpeed);
    }
	return (1);
}

int		lodev(t_all *all)
{
	int		x;

	all->img.img = mlx_new_image(all->mlx, all->map.x, all->map.y);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp,
								&all->img.line_len, &all->img.endian);

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
			if (all->map.map[all->lodev.mapY][all->lodev.mapX] == '1')
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

		all->lodev.moveSpeed = 0.05;
		all->lodev.rotSpeed = 0.15;

		while (all->lodev.drawStart <= all->lodev.drawEnd)
		{
			// mlx_pixel_put(all->mlx, all->win, x, all->lodev.drawStart, all->plr.color);
			pixel_put(&all->img, x, all->lodev.drawStart, all->plr.color);
			all->lodev.drawStart++;
		}
		x++;
	}

	mlx_hook(all->win, 2, (1L<<0), key_press, all);
    mlx_hook(all->win, 17, (1L<<0),	close_window, all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	// mlx_destroy_image(all->mlx, all->img.img);
	return (0);
}
