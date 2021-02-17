/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:07:24 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/14 00:25:21 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	error(char *error)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(error, 1);
	exit(0);
}

int		color_check(char **color)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (ft_atoi(color[i]) < 0 || ft_atoi(color[i]) > 255 ||
						!ft_isdigit_str(color[i]))
			return (0);
		i++;
	}
	return (1);
}
