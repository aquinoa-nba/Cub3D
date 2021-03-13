/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_floor_n_ceilling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:08:45 by aquinoa           #+#    #+#             */
/*   Updated: 2021/03/13 16:54:43 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	pars_floor(t_all *all)
{
	char	**sp_line;

	sp_line = NULL;
	if (!all->cflag.fl && (all->cflag.fl = 1))
	{
		!ft_strrncmp(all->line, " ", 1) ?
					error("Space after Floor config!") : 0;
		all->line++;
		check_space(all);
		!(sp_line = ft_split(all->line, ',')) || ft_array_len(sp_line) != 3 ||
		!color_check(sp_line) ? error("Incorrect Floor color!") : 0;
		all->txrs.fl = ft_atoi(sp_line[0]) << 16 | ft_atoi(sp_line[1]) << 8
										| ft_atoi(sp_line[2]);
	}
	else
		error("Duplicated Floor config!");
	ft_free_array(sp_line);
}

void	pars_ceiling(t_all *all)
{
	char	**sp_line;

	sp_line = NULL;
	if (!all->cflag.ceil && (all->cflag.ceil = 1))
	{
		!ft_strrncmp(all->line, " ", 1) ?
					error("Space after Ceiling config!") : 0;
		all->line++;
		check_space(all);
		!(sp_line = ft_split(all->line, ',')) || ft_array_len(sp_line) != 3 ||
		!color_check(sp_line) ? error("Incorrect Ceiling color!") : 0;
		all->txrs.ceil = ft_atoi(sp_line[0]) << 16 | ft_atoi(sp_line[1]) << 8
										| ft_atoi(sp_line[2]);
	}
	else
		error("Duplicated Ceiling config!");
	ft_free_array(sp_line);
}

void	pars_floor_n_ceilling(t_all *all)
{
	int		i;
	int		n;

	n = 0;
	i = -1;
	while (all->line[++i])
		all->line[i] == ',' ? n++ : 0;
	n != 2 ? error("Incorrect Floor or Ceiling config!") : 0;
	*all->line == 'F' ? pars_floor(all) : 0;
	*all->line == 'C' ? pars_ceiling(all) : 0;
}
