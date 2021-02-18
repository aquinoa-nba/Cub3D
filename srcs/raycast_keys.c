/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:53:41 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/18 18:32:29 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		close_window(t_all *all)
{
	mlx_destroy_window(all->mlx, all->win);
	exit(0);
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
	return (1);
}
