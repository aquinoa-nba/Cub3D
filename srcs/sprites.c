/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:55:24 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/17 22:20:37 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

#include <stdio.h>

void	swap(t_sprt *sprts, int i, int j)
{
	t_sprt	tmp;

	tmp = sprts[i];
	sprts[i] = sprts[j];
	sprts[j] = tmp;
}

void	sort_prites(t_sprt *sprts, int left, int right)
{
	int		i;
	int		j;
	double	pos;

	i = left;
	j = right;
	pos = sprts[(left + right) / 2].dist;
	while (i <= j)
	{
		while (sprts[i].dist > pos)
			i++;
		while (sprts[j].dist < pos)
			j--;
		if (i <= j)
		{
			if (sprts[i].dist < sprts[j].dist)
				swap(sprts, i, j);
			i++;
			j--;
		}
	}
	left < j ? sort_prites(sprts, left, j) : 0;
	i < right ? sort_prites(sprts, i, right) : 0;
}

void	sprite_cast(t_all *all, double *perp_buf)
{
	int		i;
	int		j;
	int		n;
	t_sprt	sprts[all->rc.sprts_count];
	t_img	sprt;

	i = -1;
	n = 0;
	while (all->map[++i])
	{
		j = -1;
		while (all->map[i][++j])
		{
			if (all->map[i][j] == '2' && n++)
			{
				sprts[n].x = i + 0.5;
				sprts[n].y = j + 0.5;
			}
		}
	}

	i = -1;
	while (++i < all->rc.sprts_count)
		sprts[i].dist = ((all->rc.p_x - sprts[i].x) *
		(all->rc.p_x - sprts[i].x) + (all->rc.p_y - sprts[i].y) *
					(all->rc.p_y - sprts[i].y));

	sort_prites(sprts, 0, all->rc.sprts_count - 1);

	sprt.img = mlx_xpm_file_to_image(all->mlx, all->txrs.spr,
				&all->sprt_w, &all->sprt_h);

	sprt.addr = mlx_get_data_addr(sprt.img, &sprt.bpp,
			   &sprt.line_len, &sprt.endian);

	i = -1;
	while (++i < all->rc.sprts_count)
	{
		if (sprts[i].dist < 30000.0)
		{
			all->rc.spr_x = sprts[i].x - all->rc.p_x;
			all->rc.spr_y = sprts[i].y - all->rc.p_y;

			all->rc.invDet = 1.0 / (all->rc.v_cam_x * all->rc.p_dir_y - all->rc.p_dir_x * all->rc.v_cam_y);

			all->rc.trnfrm_x = all->rc.invDet * (all->rc.p_dir_y * all->rc.spr_x - all->rc.p_dir_x * all->rc.spr_y);
			all->rc.trnfrm_y = all->rc.invDet * (-all->rc.v_cam_y * all->rc.spr_x + all->rc.v_cam_x * all->rc.spr_y);

			all->rc.spr_scr_x = (int)(( all->res_w / 2) * (1 + all->rc.trnfrm_x / all->rc.trnfrm_y));

			all->rc.spr_height = abs((int)(all->res_h / (all->rc.trnfrm_y)));
			all->rc.draw_start_y = -all->rc.spr_height / 2 + all->res_h / 2;
			if(all->rc.draw_start_y < 0) all->rc.draw_start_y = 0;
			all->rc.draw_end_y = all->rc.spr_height / 2 + all->res_h / 2;
			if(all->rc.draw_end_y >= all->res_h) all->rc.draw_end_y = all->res_h - 1;

			all->rc.sprite_width = abs( (int) (all->res_h / (all->rc.trnfrm_y)));
			all->rc.draw_start_x = -all->rc.sprite_width / 2 + all->rc.spr_scr_x;
			if(all->rc.draw_start_x < 0) all->rc.draw_start_x = 0;
			all->rc.draw_end_x = all->rc.sprite_width / 2 + all->rc.spr_scr_x;
			if(all->rc.draw_end_x >= all->res_w) all->rc.draw_end_x =  all->res_w - 1;

			for(all->rc.stripe = all->rc.draw_start_x; all->rc.stripe < all->rc.draw_end_x; all->rc.stripe++)
			{
				all->rc.tex_x = (int)(256 * (all->rc.stripe - (-all->rc.sprite_width / 2 + all->rc.spr_scr_x)) * all->sprt_w / all->rc.sprite_width) / 256;
				if(all->rc.trnfrm_y > 0 && all->rc.stripe > 0 && all->rc.stripe <  all->res_w && all->rc.trnfrm_y < perp_buf[all->rc.stripe])
				for(int y = all->rc.draw_start_y; y < all->rc.draw_end_y; y++)
				{
					int d = (y) * 256 - all->res_h * 128 + all->rc.spr_height * 128;
					all->rc.tex_y = ((d * all->sprt_h) / all->rc.spr_height) / 256;
					int color = get_color(&sprt, all->rc.tex_x, all->rc.tex_y);
					if((color & 0x00FFFFFF) != 0) pixel_put(&all->img, all->rc.stripe, y, color);
				}
			}
		}
	}
}