/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:20:34 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/16 21:35:23 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	check_zero(int i, int j, t_flags *flags, t_all *all)
{
	if (all->map[i][j] == '0' || all->map[i][j] == '2' ||
		(!flags->no && !flags->so && !flags->we && !flags->ea &&
						all->map[i][j] == 'N' && (flags->no = 1)) ||
		(!flags->no && !flags->so && !flags->we && !flags->ea &&
						all->map[i][j] == 'S' && (flags->so = 1)) ||
		(!flags->no && !flags->so && !flags->we && !flags->ea &&
						all->map[i][j] == 'W' && (flags->we = 1)) ||
		(!flags->no && !flags->so && !flags->we && !flags->ea &&
						all->map[i][j] == 'E' && (flags->ea = 1)))
	{
		(all->map[i - 1][j - 1] == ' ' || all->map[i - 1][j] == ' ' ||
		all->map[i - 1][j + 1] == ' ' || all->map[i][j - 1] == ' ' ||
		all->map[i][j + 1] == ' ' || all->map[i + 1][j - 1] == ' ' ||
		all->map[i + 1][j] == ' ' || all->map[i + 1][j + 1] == ' ') ?
											error("Invalid map!") : 0;
		all->map[i][j] == '2' ? all->rc.sprts_count++ : 0;
	}
	else if (all->map[i][j] != '1' && all->map[i][j] != '2' && all->map[i][j]
		!= '0' && all->map[i][j] != ' ')
		error("Invalid map!");
}

void	inside_check(int i, t_flags *flags, t_all *all)
{
	int		j;
	char	*tmp;

	!(tmp = ft_strtrim(all->map[i], " \t")) ? error("Memory error!") : 0;
	if (tmp[0] != '1' || tmp[ft_strlen(tmp) - 1] != '1')
		error("Map is not closed!");
	free(tmp);
	j = -1;
	while (all->map[i][++j])
		check_zero(i, j, flags, all);
}

void	validator(int len, t_all *all)
{
	int		i;
	int		j;
	t_flags	*flags;

	!(flags = (ft_calloc(1, sizeof(t_flags)))) ? error("Memory error!") : 0;
	i = -1;
	while (all->map[++i])
	{
		if (i == 0 || i == len)
		{
			j = -1;
			while (all->map[i][++j])
			{
				if (!(all->map[i][j] == '1' || all->map[i][j] == ' '))
					error("Wrong symbol on the map!");
				else if (all->map[i][j] == '0')
					error("Map is not closed!");
			}
		}
		else
			inside_check(i, flags, all);
	}
	!flags->no && !flags->so && !flags->we && !flags->ea ? error("No player!")
								: free(flags);
}
