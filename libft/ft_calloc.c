/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:43:08 by aquinoa           #+#    #+#             */
/*   Updated: 2020/11/12 15:41:17 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buf;
	char	*buf2;
	size_t	bufsize;

	bufsize = size * count;
	if (!(buf = malloc(bufsize)))
		return (NULL);
	buf2 = buf;
	while (bufsize > 0)
	{
		*buf2 = 0;
		buf2++;
		bufsize--;
	}
	return (buf);
}
