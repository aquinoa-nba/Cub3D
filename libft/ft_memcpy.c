/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:30:52 by aquinoa           #+#    #+#             */
/*   Updated: 2020/11/10 00:57:52 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_2;
	const unsigned char	*src_2;

	if (dst != src)
	{
		dst_2 = dst;
		src_2 = src;
		while (n--)
			*dst_2++ = *src_2++;
	}
	return (dst);
}
