/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:16:06 by aquinoa           #+#    #+#             */
/*   Updated: 2020/12/01 20:27:08 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char		*sub_str;
	size_t		str_len;
	size_t		sub_str_len;

	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	sub_str_len = 0;
	if (start >= str_len)
	{
		if (!(sub_str = (char*)malloc(1)))
			return (NULL);
	}
	else
	{
		if (len > (str_len - start))
			len = str_len - start;
		if (!(sub_str = (char*)malloc(len + 1)))
			return (NULL);
		sub_str_len = len;
		while (len--)
			*sub_str++ = str[start++];
	}
	*sub_str = '\0';
	return (sub_str - sub_str_len);
}
