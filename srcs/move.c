/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:45:55 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/18 18:31:49 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	go(t_all *all)
{
	if (all->map[(int)(all->rc.p_x - (all->rc.v_cam_y) *
			all->rc.move_speed)][(int)(all->rc.p_y)] == '0')
		all->rc.p_x -= all->rc.v_cam_y * all->rc.move_speed;
	if (all->map[(int)(all->rc.p_x)][(int)(all->rc.p_y +
					(all->rc.v_cam_x) * all->rc.move_speed)] == '0')
		all->rc.p_y += all->rc.v_cam_x * all->rc.move_speed;
}

void	back(t_all *all)
{
	if (all->map[(int)(all->rc.p_x + (all->rc.v_cam_y) *
			all->rc.move_speed)][(int)(all->rc.p_y)] == '0')
		all->rc.p_x += all->rc.v_cam_y * all->rc.move_speed;
	if (all->map[(int)(all->rc.p_x)][(int)(all->rc.p_y -
					(all->rc.v_cam_x) * all->rc.move_speed)] == '0')
		all->rc.p_y -= all->rc.v_cam_x * all->rc.move_speed;
}

void	move_right(t_all *all)
{
	if (all->map[(int)(all->rc.p_x + all->rc.v_cam_x *
			all->rc.move_speed)][(int)(all->rc.p_y)] == '0')
		all->rc.p_x += all->rc.v_cam_x * all->rc.move_speed;
	if (all->map[(int)(all->rc.p_x)][(int)(all->rc.p_y +
					all->rc.v_cam_y * all->rc.move_speed)] == '0')
		all->rc.p_y += all->rc.v_cam_y * all->rc.move_speed;
}

void	move_left(t_all *all)
{
	if (all->map[(int)(all->rc.p_x - all->rc.v_cam_x *
			all->rc.move_speed)][(int)(all->rc.p_y)] == '0')
		all->rc.p_x -= all->rc.v_cam_x * all->rc.move_speed;
	if (all->map[(int)(all->rc.p_x)][(int)(all->rc.p_y -
					all->rc.v_cam_y * all->rc.move_speed)] == '0')
		all->rc.p_y -= all->rc.v_cam_y * all->rc.move_speed;
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
