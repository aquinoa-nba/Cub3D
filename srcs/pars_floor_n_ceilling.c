/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_floor_n_ceilling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:08:45 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/17 15:30:31 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	pars_floor(t_all *all)
{
	char	**split_line;

	split_line = NULL;
	if (!all->cflag.fl && (all->cflag.fl = 1))
	{
		!ft_strrncmp(all->line, " ", 1) ?
					error("Space after Floor config!") : 0;
		all->line++;
		while (*all->line == ' ')
			all->line++;
		!(split_line = ft_split(all->line, ',')) ||
		!color_check(split_line) ? error("Incorrect Floor color!") : 0;
		ft_array_len(split_line) == 3 ? all->txrs.fl =
					ft_atoi(split_line[0]) << 16 | ft_atoi(split_line[1]) << 8
										| ft_atoi(split_line[2]) : 0;
	}
	else
		error("Incorrect Floor config!");
	ft_free_array(split_line);
}

void	pars_ceilling(t_all *all)
{
	char	**split_line;

	split_line = NULL;
	if (!all->cflag.ceil && (all->cflag.ceil = 1))
	{
		!ft_strrncmp(all->line, " ", 1) ?
					error("Space after Ceilling config!") : 0;
		all->line++;
		while (*all->line == ' ')
			all->line++;
		!(split_line = ft_split(all->line, ',')) ||
		!color_check(split_line) ? error("Incorrect Ceilling color!") : 0;
		ft_array_len(split_line) == 3 ? all->txrs.ceil =
					ft_atoi(split_line[0]) << 16 | ft_atoi(split_line[1]) << 8
										| ft_atoi(split_line[2]) : 0;
	}
	else
		error("Incorrect Ceilling config!");
	ft_free_array(split_line);
}

void	pars_floor_n_ceilling(t_all *all)
{
	int		i;
	int		n;

	n = 0;
	i = -1;
	while (all->line[++i])
		all->line[i] == ',' ? n++ : 0;
	n != 2 ? error("Incorrect Floor or Ceilling config!") : 0;
	*all->line == 'F' ? pars_floor(all) : 0;
	*all->line == 'C' ? pars_ceilling(all) : 0;
}
