/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 23:05:31 by aquinoa           #+#    #+#             */
/*   Updated: 2021/01/30 17:19:05 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	error(int	error_num)
{
	if (error_num == 1)
	{
		ft_putendl_fd("Error", 1);
		ft_putendl_fd("Incorrect configuration!", 1);
		exit (0);
	}
}