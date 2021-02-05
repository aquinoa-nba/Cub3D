/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:20:34 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/05 15:41:59 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	check_zero(int i, int j, t_flags *flags, t_map map)
{
	if (map.map[i][j] == '0' ||
		(!flags->no && !flags->so && !flags->we && !flags->ea &&
						map.map[i][j] == 'N' && (flags->no = 1)) ||
		(!flags->no && !flags->so && !flags->we && !flags->ea &&
						map.map[i][j] == 'S' && (flags->so = 1)) ||
		(!flags->no && !flags->so && !flags->we && !flags->ea &&
						map.map[i][j] == 'W' && (flags->we = 1)) ||
		(!flags->no && !flags->so && !flags->we && !flags->ea &&
						map.map[i][j] == 'E' && (flags->ea = 1)))
	{
		(map.map[i - 1][j - 1] == ' ' || map.map[i - 1][j] == ' ' ||
		map.map[i - 1][j + 1] == ' ' || map.map[i][j - 1] == ' ' ||
		map.map[i][j + 1] == ' ' || map.map[i + 1][j - 1] == ' ' ||
		map.map[i + 1][j] == ' ' || map.map[i + 1][j + 1] == ' ') ?
											error("Invalid map!") : 0;
	}
	else if (map.map[i][j] != '1' && map.map[i][j] != '2' && map.map[i][j]
		!= '0' && map.map[i][j] != ' ')
		error("Invalid map!");
}

void	inside_check(int i, t_flags *flags, t_map map)
{
	int		j;
	char	*tmp;

	!(tmp = ft_strtrim(map.map[i], " \t")) ? error("Memory error!") : 0;
	if (tmp[0] != '1' || tmp[ft_strlen(tmp) - 1] != '1')
		error("Map is not closed!");
	free(tmp);
	j = -1;
	while (map.map[i][++j])
		check_zero(i, j, flags, map);
}

void	validator(int len, t_all *all)
{
	int		i;
	int		j;
	t_flags	*flags;
	t_map	map;

	map = all->map;
	!(flags = (ft_calloc(1, sizeof(t_flags)))) ? error("Memory error!") : 0;
	i = -1;
	while (map.map[++i])
	{
		if (i == 0 || i == len)
		{
			j = -1;
			while (map.map[i][++j])
				(map.map[i][j] != '1' && map.map[i][j] != ' ') ?
					error("Map is not closed!") : 0;
		}
		else
			inside_check(i, flags, map);
	}
	!flags->no && !flags->so && !flags->we && !flags->ea ? error("No player!")
								: free(flags);
}
