/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:15:59 by aquinoa           #+#    #+#             */
/*   Updated: 2020/11/12 17:20:28 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t len;

	len = ft_strlen(s);
	if (c == '\0')
		return ((char*)s + len);
	while (len--)
	{
		if (s[len] == c)
		{
			return ((char*)s + len);
		}
	}
	return (0);
}
