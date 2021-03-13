/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 23:46:16 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/22 19:58:51 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	check_space(t_all *all)
{
	if (*all->line == ' ')
	{
		while (*all->line == ' ')
			all->line++;
	}
	else
		error("Missing space after type!");
}

void	pars_no(t_all *all)
{
	if (!all->cflag.no && !ft_strncmp(all->line, "NO", 2) &&
			(all->cflag.no = 1))
	{
		!ft_strrncmp(all->line, " ", 1) ? error("Space after NO config!") : 0;
		ft_strrncmp(all->line, ".xpm", 4) ? error("Wrong NO format!") : 0;
		all->line += 2;
		check_space(all);
		if (!(all->txrs.no = ft_strdup(all->line)))
			error("Memory error!");
	}
	else
		error("Incorrect NO config!");
}

void	pars_so_and_sprt(t_all *all)
{
	if (!all->cflag.so && !ft_strncmp(all->line, "SO", 2) &&
			(all->cflag.so = 1))
	{
		!ft_strrncmp(all->line, " ", 1) ? error("Space after SO config!") : 0;
		ft_strrncmp(all->line, ".xpm", 4) ? error("Wrong SO format!") : 0;
		all->line += 2;
		check_space(all);
		if (!(all->txrs.so = ft_strdup(all->line)))
			error("Memory error!");
	}
	else if (!ft_strncmp(all->line, "SO ", 2))
		all->cflag.so ? error("Duplicated SO config!") :
						error("Incorrect SO config!");
	if (!all->cflag.spr && !ft_strncmp(all->line, "S ", 1) &&
			(all->cflag.spr = 1))
	{
		ft_strrncmp(all->line, ".xpm", 4) ? error("Wrong S format!") : 0;
		all->line += 1;
		check_space(all);
		if (!(all->txrs.spr = ft_strdup(all->line)))
			error("Memory error!");
	}
	else if (!ft_strncmp(all->line, "S ", 1))
		all->cflag.spr ? error("Duplicated Sprite config!") :
						error("Incorrect Sprite config!");
}

void	pars_we(t_all *all)
{
	if (!all->cflag.we && !ft_strncmp(all->line, "WE", 2) &&
													(all->cflag.we = 1))
	{
		!ft_strrncmp(all->line, " ", 1) ? error("Space after WE config!") : 0;
		ft_strrncmp(all->line, ".xpm", 4) ? error("Wrong WE format!") : 0;
		all->line += 2;
		check_space(all);
		if (!(all->txrs.we = ft_strdup(all->line)))
			error("Memory error!");
	}
	else
		error("Incorrect WE config!");
}

void	pars_ea(t_all *all)
{
	if (!all->cflag.ea && !ft_strncmp(all->line, "EA", 2) &&
													(all->cflag.ea = 1))
	{
		!ft_strrncmp(all->line, " ", 1) ? error("Space after EA config!") : 0;
		ft_strrncmp(all->line, ".xpm", 4) ? error("Wrong EA format!") : 0;
		all->line += 2;
		check_space(all);
		if (!(all->txrs.ea = ft_strdup(all->line)))
			error("Memory error!");
	}
	else
		error("Incorrect EA config!");
}
