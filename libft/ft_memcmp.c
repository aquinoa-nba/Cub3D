/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:06:49 by aquinoa           #+#    #+#             */
/*   Updated: 2020/11/10 00:57:01 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *buf_s1;
	const unsigned char *buf_s2;

	buf_s1 = s1;
	buf_s2 = s2;
	while (n--)
	{
		if (*buf_s1 != *buf_s2)
			return (*buf_s1 - *buf_s2);
		buf_s1++;
		buf_s2++;
	}
	return (0);
}
