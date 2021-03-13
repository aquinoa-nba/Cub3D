/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:55:54 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/22 18:37:40 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_array_len(char **array)
{
	int		len;

	if (!*array)
		return (0);
	len = 0;
	while (array[len])
	{
		len++;
	}
	return (len);
}
