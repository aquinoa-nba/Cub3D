/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 09:57:40 by aquinoa           #+#    #+#             */
/*   Updated: 2020/11/12 16:56:47 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s1_dup;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	if (!(s1_dup = ft_calloc(s1_len + 1, sizeof(char))))
		return (NULL);
	while (*s1)
		*s1_dup++ = *s1++;
	return (s1_dup - s1_len);
}
