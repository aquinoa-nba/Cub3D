/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:36:58 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/18 12:38:13 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	swap(t_sprt *sprts, int i, int j)
{
	t_sprt	tmp;

	tmp = sprts[i];
	sprts[i] = sprts[j];
	sprts[j] = tmp;
}

void	sort_sprites(t_sprt *sprts, int left, int right)
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
	left < j ? sort_sprites(sprts, left, j) : 0;
	i < right ? sort_sprites(sprts, i, right) : 0;
}
