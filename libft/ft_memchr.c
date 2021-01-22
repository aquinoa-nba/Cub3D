/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 13:40:27 by aquinoa           #+#    #+#             */
/*   Updated: 2020/11/14 15:12:56 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_2;
	size_t			i;

	s_2 = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if (s_2[i] == (unsigned char)c)
			return (s_2 + i);
		i++;
	}
	return (NULL);
}
