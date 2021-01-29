/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 23:05:31 by aquinoa           #+#    #+#             */
/*   Updated: 2021/01/28 23:20:06 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	error(int	error_num)
{
	if (error_num == 1)
	{
		ft_putendl_fd("Configuration error!", 1);
		exit (0);
	}
}