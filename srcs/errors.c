/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 23:05:31 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/03 16:56:30 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	error(char *error)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(error, 1);
	exit(0);
}
