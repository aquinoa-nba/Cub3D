/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:26:46 by aquinoa           #+#    #+#             */
/*   Updated: 2020/11/12 15:54:28 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_represent(char *s, long nbr, int count)
{
	if (nbr < 0)
	{
		while (count)
		{
			s[count - 1] = -nbr % 10 + '0';
			nbr /= 10;
			count--;
		}
		s[0] = '-';
	}
	else
	{
		while (count)
		{
			s[count - 1] = nbr % 10 + '0';
			nbr /= 10;
			count--;
		}
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		count;
	long	nbr;

	nbr = n;
	count = 0;
	if (n == 0 || n == -0)
		count++;
	while (n)
	{
		n /= 10;
		count++;
	}
	if (nbr < 0)
		count++;
	if (!(s = (char*)ft_calloc(count + 1, sizeof(char))))
		return (NULL);
	ft_represent(s, nbr, count);
	return (s);
}
