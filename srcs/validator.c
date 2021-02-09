/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:20:34 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/09 19:24:30 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	check_zero(int i, int j, t_flags *flags, t_all *all)
{
	if (all->map.map[i][j] == '0' || all->map.map[i][j] == '2' ||
		(!flags->no && !flags->so && !flags->we && !flags->ea &&
						all->map.map[i][j] == 'N' && (flags->no = 1)) ||
		(!flags->no && !flags->so && !flags->we && !flags->ea &&
						all->map.map[i][j] == 'S' && (flags->so = 1)) ||
		(!flags->no && !flags->so && !flags->we && !flags->ea &&
						all->map.map[i][j] == 'W' && (flags->we = 1)) ||
		(!flags->no && !flags->so && !flags->we && !flags->ea &&
						all->map.map[i][j] == 'E' && (flags->ea = 1)))
	{
		(all->map.map[i - 1][j - 1] == ' ' || all->map.map[i - 1][j] == ' ' ||
		all->map.map[i - 1][j + 1] == ' ' || all->map.map[i][j - 1] == ' ' ||
		all->map.map[i][j + 1] == ' ' || all->map.map[i + 1][j - 1] == ' ' ||
		all->map.map[i + 1][j] == ' ' || all->map.map[i + 1][j + 1] == ' ') ?
											error("Invalid map!") : 0;
		all->map.map[i][j] == '2' ? all->rc.numSprites++ : 0;
	}
	else if (all->map.map[i][j] != '1' && all->map.map[i][j] != '2' && all->map.map[i][j]
		!= '0' && all->map.map[i][j] != ' ')
		error("Invalid map!");
}

void	inside_check(int i, t_flags *flags, t_all *all)
{
	int		j;
	char	*tmp;

	!(tmp = ft_strtrim(all->map.map[i], " \t")) ? error("Memory error!") : 0;
	if (tmp[0] != '1' || tmp[ft_strlen(tmp) - 1] != '1')
		error("Map is not closed!");
	free(tmp);
	j = -1;
	while (all->map.map[i][++j])
		check_zero(i, j, flags, all);
}

void	validator(int len, t_all *all)
{
	int		i;
	int		j;
	t_flags	*flags;
	// t_map	map;

	// map = all->map;
	!(flags = (ft_calloc(1, sizeof(t_flags)))) ? error("Memory error!") : 0;
	i = -1;
	while (all->map.map[++i])
	{
		if (i == 0 || i == len)
		{
			j = -1;
			while (all->map.map[i][++j])
				(all->map.map[i][j] != '1' && all->map.map[i][j] != ' ') ?
					error("Map is not closed!") : 0;
		}
		else
			inside_check(i, flags, all);
	}
	!flags->no && !flags->so && !flags->we && !flags->ea ? error("No player!")
								: free(flags);
}
