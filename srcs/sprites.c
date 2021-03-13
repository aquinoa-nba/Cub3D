/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:55:24 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/22 20:24:02 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	sprites_arr(t_sprt *sprts, t_all *all)
{
	int		i;
	int		j;
	int		n;

	n = 0;
	i = -1;
	while (all->map[++i])
	{
		j = -1;
		while (all->map[i][++j])
		{
			if (all->map[i][j] == '2')
			{
				sprts[n].x = i + 0.5;
				sprts[n].y = j + 0.5;
				n++;
			}
		}
	}
}

void	draw_sprite(double *perp_buf, t_all *all)
{
	int		y;
	int		d;

	while (++all->rc.stripe < all->rc.draw_end_x)
	{
		all->rc.tex_x = (int)(256 * (all->rc.stripe - (-all->rc.sprite_width /
		2 + all->rc.spr_scr_x)) * all->sprt_w / all->rc.sprite_width) / 256;
		if (all->rc.trnfrm_y > 0 && all->rc.stripe > 0 && all->rc.stripe <
			all->res_w && all->rc.trnfrm_y < perp_buf[all->rc.stripe])
		{
			y = all->rc.draw_start_y - 1;
			while (++y < all->rc.draw_end_y)
			{
				d = (y) * 256 - all->res_h * 128 + all->rc.spr_height * 128;
				all->rc.tex_y = ((d * all->sprt_h) / all->rc.spr_height) / 256;
				all->color = get_color(&all->txr[4],
												all->rc.tex_x, all->rc.tex_y);
				if ((all->color & 0x00FFFFFF) != 0)
					pixel_put(&all->img, all->rc.stripe, y, all->color);
			}
		}
	}
}

void	sprite_width_n_height(t_all *all)
{
	all->rc.sprite_width = fabs((double)all->res_h / all->rc.trnfrm_y);
	all->rc.draw_start_x = -all->rc.sprite_width / 2 + all->rc.spr_scr_x;
	if (all->rc.draw_start_x < 0)
		all->rc.draw_start_x = 0;
	all->rc.draw_end_x = all->rc.sprite_width / 2 + all->rc.spr_scr_x;
	if (all->rc.draw_end_x >= all->res_w)
		all->rc.draw_end_x = all->res_w - 1;
	all->rc.spr_height = fabs((double)all->res_h / all->rc.trnfrm_y);
	all->rc.draw_start_y = -all->rc.spr_height / 2 + all->res_h / 2;
	if (all->rc.draw_start_y < 0)
		all->rc.draw_start_y = 0;
	all->rc.draw_end_y = all->rc.spr_height / 2 + all->res_h / 2;
	if (all->rc.draw_end_y >= all->res_h)
		all->rc.draw_end_y = all->res_h - 1;
}

void	sprite_casting(double *perp_buf, t_sprt *sprts, t_all *all)
{
	int		i;

	i = -1;
	while (++i < all->rc.sprts_count)
	{
		if (sprts[i].dist < 30000.0)
		{
			all->rc.spr_x = sprts[i].x - all->rc.p_x;
			all->rc.spr_y = sprts[i].y - all->rc.p_y;
			all->rc.inv_mtrx = 1.0 / (all->rc.v_cam_x * all->rc.p_dir_y -
											all->rc.p_dir_x * all->rc.v_cam_y);
			all->rc.trnfrm_x = all->rc.inv_mtrx * (all->rc.p_dir_y *
							all->rc.spr_x - all->rc.p_dir_x * all->rc.spr_y);
			all->rc.trnfrm_y = all->rc.inv_mtrx * (-all->rc.v_cam_y *
							all->rc.spr_x + all->rc.v_cam_x * all->rc.spr_y);
			all->rc.spr_scr_x = ((all->res_w / 2) *
									(1 + all->rc.trnfrm_x / all->rc.trnfrm_y));
			sprite_width_n_height(all);
			all->rc.stripe = all->rc.draw_start_x - 1;
			draw_sprite(perp_buf, all);
		}
	}
}

void	sprites(t_all *all, double *perp_buf)
{
	int		i;
	t_sprt	sprts[all->rc.sprts_count];

	sprites_arr(sprts, all);
	i = -1;
	while (++i < all->rc.sprts_count)
	{
		sprts[i].dist = ((all->rc.p_x - sprts[i].x) *
			(all->rc.p_x - sprts[i].x) + (all->rc.p_y - sprts[i].y) *
					(all->rc.p_y - sprts[i].y));
	}
	sort_sprites(sprts, 0, all->rc.sprts_count - 1);
	sprite_casting(perp_buf, sprts, all);
}
