/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 23:46:16 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/17 15:30:29 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	pars_no(t_all *all)
{
	if (!all->cflag.no && !ft_strncmp(all->line, "NO", 2) &&
													(all->cflag.no = 1))
	{
		all->line += 2;
		while (*all->line == ' ')
			all->line++;
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
		all->line += 2;
		while (*all->line == ' ')
			all->line++;
		if (!(all->txrs.so = ft_strdup(all->line)))
			error("Memory error!");
	}
	else if (!ft_strncmp(all->line, "SO", 2))
		error("Incorrect SO config!");
	if (!all->cflag.spr && !ft_strncmp(all->line, "S ", 2) &&
													(all->cflag.spr = 1))
	{
		all->line++;
		while (*all->line == ' ')
			all->line++;
		if (!(all->txrs.spr = ft_strdup(all->line)))
			error("Memory error!");
	}
	else if (!ft_strncmp(all->line, "S ", 2))
		error("Incorrect Sprite config!");
}

void	pars_we(t_all *all)
{
	if (!all->cflag.we && !ft_strncmp(all->line, "WE", 2) &&
													(all->cflag.we = 1))
	{
		all->line += 2;
		while (*all->line == ' ')
			all->line++;
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
		all->line += 2;
		while (*all->line == ' ')
			all->line++;
		if (!(all->txrs.ea = ft_strdup(all->line)))
			error("Memory error!");
	}
	else
		error("Incorrect EA config!");
}
