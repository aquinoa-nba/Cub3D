/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:48:26 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/18 12:51:02 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	right(t_all *all)
{
	all->rc.old_dir_x = all->rc.p_dir_x;
	all->rc.p_dir_x = all->rc.p_dir_x * cos(-all->rc.rot_speed) -
						all->rc.p_dir_y * sin(-all->rc.rot_speed);
	all->rc.p_dir_y = all->rc.old_dir_x * sin(-all->rc.rot_speed) +
							all->rc.p_dir_y * cos(-all->rc.rot_speed);
	all->rc.oldv_cam_x = all->rc.v_cam_x;
	all->rc.v_cam_x = all->rc.v_cam_x * cos(-all->rc.rot_speed) -
							all->rc.v_cam_y * sin(-all->rc.rot_speed);
	all->rc.v_cam_y = all->rc.oldv_cam_x * sin(-all->rc.rot_speed) +
							all->rc.v_cam_y * cos(-all->rc.rot_speed);
}

void	left(t_all *all)
{
	all->rc.old_dir_x = all->rc.p_dir_x;
	all->rc.p_dir_x = all->rc.p_dir_x * cos(all->rc.rot_speed) -
						all->rc.p_dir_y * sin(all->rc.rot_speed);
	all->rc.p_dir_y = all->rc.old_dir_x * sin(all->rc.rot_speed) +
							all->rc.p_dir_y * cos(all->rc.rot_speed);
	all->rc.oldv_cam_x = all->rc.v_cam_x;
	all->rc.v_cam_x = all->rc.v_cam_x * cos(all->rc.rot_speed) -
							all->rc.v_cam_y * sin(all->rc.rot_speed);
	all->rc.v_cam_y = all->rc.oldv_cam_x * sin(all->rc.rot_speed) +
							all->rc.v_cam_y * cos(all->rc.rot_speed);
}
