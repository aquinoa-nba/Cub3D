/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 21:26:00 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/05 14:28:57 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double			represent(t_args arg)
{
	while (arg.i)
	{
		arg.frac = arg.frac / 10;
		arg.i--;
	}
	arg.nb = arg.whole_frac + arg.frac;
	if (arg.flag)
		arg.nb *= -1;
	return (arg.nb);
}

double			ft_atof(char *str)
{
	t_args	arg;

	arg.nb = 0;
	arg.whole_frac = 0;
	arg.frac = 0;
	arg.i = 0;
	while (*str == '-' || *str == '+')
	{
		arg.flag = (*str == '-' ? 1 : 0);
		arg.flag ? str++ : 0;
		*str == '+' ? str++ : 0;
	}
	while (ft_isdigit(*str))
	{
		arg.whole_frac = arg.whole_frac * 10 + (*str - 48);
		str++;
	}
	if (*str == '.' || *str == ',')
		str++;
	while (ft_isdigit(*str) && ++arg.i)
	{
		arg.frac = arg.frac * 10 + (*str - 48);
		str++;
	}
	return (represent(arg));
}
