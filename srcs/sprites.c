/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:55:24 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/08 21:40:28 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	sprite_cast(t_all *all)
{
	int	texWidth;
	int	texHeight;
	t_img	sprt;

	sprt.img = mlx_xpm_file_to_image(all->mlx, all->map.texture.spr, &texWidth, &texHeight);

	sprt.addr = mlx_get_data_addr(sprt.img, &sprt.bpp,
			   &sprt.line_len, &sprt.endian);

	// for(int i = 0; i < numSprites; i++)
	    // {
	      double spriteX = 10 - all->rc.posX;
	      double spriteY = 10 - all->rc.posY;

	      double invDet = 1.0 / (all->rc.planeX * all->rc.dirY - all->rc.dirX * all->rc.planeY);

	      double transformX = invDet * (all->rc.dirY * spriteX - all->rc.dirX * spriteY);
	      double transformY = invDet * (-all->rc.planeY * spriteX + all->rc.planeX * spriteY);

	      int spriteScreenX = (int)(( all->map.x / 2) * (1 + transformX / transformY));

	      int spriteHeight = abs((int)(all->map.y / (transformY)));
	      int drawStartY = -spriteHeight / 2 + all->map.y / 2;
	      if(drawStartY < 0) drawStartY = 0;
	      int drawEndY = spriteHeight / 2 + all->map.y / 2;
	      if(drawEndY >= all->map.y) drawEndY = all->map.y - 1;

	      int spriteWidth = abs( (int) (all->map.y / (transformY)));
	      int drawStartX = -spriteWidth / 2 + spriteScreenX;
	      if(drawStartX < 0) drawStartX = 0;
	      int drawEndX = spriteWidth / 2 + spriteScreenX;
	      if(drawEndX >= all->map.x) drawEndX =  all->map.x - 1;

	      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
	      {
	        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
	        // if(transformY > 0 && stripe > 0 && stripe <  all->map.x && transformY < ZBuffer[stripe])
	        for(int y = drawStartY; y < drawEndY; y++)
	        {
	          int d = (y) * 256 - all->map.y * 128 + spriteHeight * 128;
	          int texY = ((d * texHeight) / spriteHeight) / 256;
	          int color = get_color(&sprt, texX, texY);
	          if((color & 0x00FFFFFF) != 0) pixel_put(&all->img, stripe, y, color);
	        }
	      }
	    // }
}