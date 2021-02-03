/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:16:40 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/03 18:17:27 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		color_check(char **color)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (ft_atoi(color[i]) < 0 || ft_atoi(color[i]) > 255 ||
						!ft_isdigit_str(color[i]))
			return (0);
		i++;
	}
	return (1);
}

void	resolution_direction(t_all *all)
{
	(((ft_strchr(all->map.sline[0], 'R')) &&
	(ft_array_len(all->map.sline) != 3)) || ((ft_strchr(all->map.sline[0], 'O')
	|| ft_strchr(all->map.sline[0], 'E')) &&
	(ft_array_len(all->map.sline) != 2))) ? error("Incorrect config!") : 0;
	if (!all->map.flags.r && ft_strchr(all->map.sline[0], 'R') &&
														(all->map.flags.r = 1))
	{
		all->map.x = ft_atoi(all->map.sline[1]);
		all->map.y = ft_atoi(all->map.sline[2]);
	}
	else if (!all->map.flags.no && !ft_strncmp(all->map.sline[0], "NO", 2) &&
													(all->map.flags.no = 1))
		all->map.texture.no = ft_strdup(all->map.sline[1]);
	else if (!all->map.flags.so && !ft_strncmp(all->map.sline[0], "SO", 2) &&
													(all->map.flags.so = 1))
		all->map.texture.so = ft_strdup(all->map.sline[1]);
	else if (!all->map.flags.we && !ft_strncmp(all->map.sline[0], "WE", 2) &&
													(all->map.flags.we = 1))
		all->map.texture.we = ft_strdup(all->map.sline[1]);
	else if (!all->map.flags.ea && !ft_strncmp(all->map.sline[0], "EA", 2) &&
													(all->map.flags.ea = 1))
		all->map.texture.ea = ft_strdup(all->map.sline[1]);
	else
		error("Incorrect configuration!");
}

void	color_parser(t_all *all)
{
	ft_array_len(all->map.sline) != 2 ? error("Incorrect configuration!") : 0;
	if (!all->map.flags.spr && !ft_strncmp(all->map.sline[0], "S", 1) &&
						(all->map.flags.spr = 1))
		all->map.texture.spr = ft_strdup(all->map.sline[1]);
	else if (!all->map.flags.fl && !ft_strncmp(all->map.sline[0], "F", 1) &&
												(all->map.flags.fl = 1))
	{
		!(all->map.f = ft_split(all->map.sline[1], ',')) ||
		!color_check(all->map.f) ? error("Incorrect configuration!") : 0;
		ft_array_len(all->map.f) == 3 ? all->map.texture.fl =
					ft_atoi(all->map.f[0]) << 16 | ft_atoi(all->map.f[1]) << 8
									| ft_atoi(all->map.f[2]) : 0;
	}
	else if (!all->map.flags.ceil && !ft_strncmp(all->map.sline[0], "C", 1) &&
												(all->map.flags.ceil = 1))
	{
		!(all->map.c = ft_split(all->map.sline[1], ',')) ||
		!color_check(all->map.c) ? error("Incorrect configuration!") : 0;
		ft_array_len(all->map.c) == 3 ? all->map.texture.ceil =
				ft_atoi(all->map.c[0]) << 16 | ft_atoi(all->map.c[1]) << 8 |
									ft_atoi(all->map.c[2]) : 0;
	}
	else
		error("Incorrect configuration!");
}

void	parser(char fd, t_list **head, t_all *all)
{
	int		gnl;

	while ((get_next_line(fd, &all->map.line)) > 0)
	{
		if (!(all->map.sline = ft_split(all->map.line, ' ')))
			error("Memory error!");
		if (*all->map.sline)
		{
			if (ft_strrncmp(all->map.sline[0], "111", 3) == 0)
				break ;
			if (ft_strchr(all->map.sline[0], 'R') ||
				ft_strchr(all->map.sline[0], 'O') ||
				ft_strchr(all->map.sline[0], 'E'))
				resolution_direction(all);
			else
				color_parser(all);
		}
		free(all->map.line);
		ft_free_array(all->map.sline);
	}
	gnl == -1 ? error("Map reading error!!") : 0;
	ft_lstadd_back(head, ft_lstnew(all->map.line));
}
