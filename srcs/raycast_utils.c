/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:15:21 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/18 15:51:34 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	check_hit_with_wall(t_all *all)
{
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
	}
}

void	ray_dist(t_all *all)
{
	if (all->rc.r_dir_x < 0)
	{
		all->rc.step_x = -1;
		all->rc.r_len0_x = (all->rc.p_x - all->rc.r_map_x) * all->rc.r_len_x;
	}
	else
	{
		all->rc.step_x = 1;
		all->rc.r_len0_x = (all->rc.r_map_x + 1.0 - all->rc.p_x) *
															all->rc.r_len_x;
	}
	if (all->rc.r_dir_y < 0)
	{
		all->rc.step_y = -1;
		all->rc.r_len0_y = (all->rc.p_y - all->rc.r_map_y) * all->rc.r_len_y;
	}
	else
	{
		all->rc.step_y = 1;
		all->rc.r_len0_y = (all->rc.r_map_y + 1.0 - all->rc.p_y) *
															all->rc.r_len_y;
	}
}

void	where_ray_hit_wall(t_all *all)
{
	if (all->rc.side == 0)
		all->rc.wall_x = all->rc.p_y + all->rc.perp_len * all->rc.r_dir_y;
	else
		all->rc.wall_x = all->rc.p_x + all->rc.perp_len * all->rc.r_dir_x;
	all->rc.wall_x -= floor((all->rc.wall_x));
	all->rc.txr_x = (all->rc.wall_x * (all->rc.txr_width));
	all->rc.txr_x = all->rc.txr_width - all->rc.txr_x - 1;
	all->rc.scale = 1.0 * all->rc.txr_height / all->rc.wall_height;
	all->rc.tex_pos = (all->rc.wall_top - all->res_h / 2
								+ all->rc.wall_height / 2) * all->rc.scale;
}

void	top_n_bot_of_wall(t_all *all)
{
	if (all->rc.side == 0)
		all->rc.perp_len = (all->rc.r_map_x - all->rc.p_x +
							(1 - all->rc.step_x) / 2) / all->rc.r_dir_x;
	else
		all->rc.perp_len = (all->rc.r_map_y - all->rc.p_y +
							(1 - all->rc.step_y) / 2) / all->rc.r_dir_y;
	all->rc.wall_height = (all->res_h / all->rc.perp_len);
	all->rc.wall_top = -all->rc.wall_height / 2 + all->res_h / 2;
	if (all->rc.wall_top < 0)
		all->rc.wall_top = 0;
	all->rc.wall_bot = all->rc.wall_height / 2 + all->res_h / 2;
	if (all->rc.wall_bot >= all->res_h)
		all->rc.wall_bot = all->res_h - 1;
}

void	ray_dir_n_dist(t_all *all)
{
	all->rc.r_dir_x = all->rc.p_dir_x + all->rc.v_cam_x * all->rc.cam_x;
	all->rc.r_dir_y = all->rc.p_dir_y + all->rc.v_cam_y * all->rc.cam_x;
	all->rc.r_map_x = (int)all->rc.p_x;
	all->rc.r_map_y = (int)all->rc.p_y;
	all->rc.r_len_x = fabs(1 / all->rc.r_dir_x);
	all->rc.r_len_y = fabs(1 / all->rc.r_dir_y);
	all->rc.hit = 0;
	ray_dist(all);
	check_hit_with_wall(all);
	where_ray_hit_wall(all);
	top_n_bot_of_wall(all);
}
