/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:16:40 by aquinoa           #+#    #+#             */
/*   Updated: 2021/01/31 22:59:28 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		chcolor(char **color)
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

int		resolution_direction(t_map *map)
{
	if ((ft_strchr(map->sline[0], 'R')) && (ft_array_len(map->sline) != 3))
		return (0);
	else if ((ft_strchr(map->sline[0], 'O') ||
			ft_strchr(map->sline[0], 'E')) && (ft_array_len(map->sline) != 2))
		return (0);
	if (!map->flags.r && ft_strchr(map->sline[0], 'R') && (map->flags.r = 1))
	{
		map->x = ft_atoi(map->sline[1]);
		map->y = ft_atoi(map->sline[2]);
	}
	else if (!map->flags.no && !ft_strncmp(map->sline[0], "NO", 2) &&
													(map->flags.no = 1))
		map->texture.no = ft_strdup(map->sline[1]);
	else if (!map->flags.so && !ft_strncmp(map->sline[0], "SO", 2) &&
													(map->flags.so = 1))
		map->texture.so = ft_strdup(map->sline[1]);
	else if (!map->flags.we && !ft_strncmp(map->sline[0], "WE", 2) &&
													(map->flags.we = 1))
		map->texture.we = ft_strdup(map->sline[1]);
	else if (!map->flags.ea && !ft_strncmp(map->sline[0], "EA", 2) &&
													(map->flags.ea = 1))
		map->texture.ea = ft_strdup(map->sline[1]);
	else
		error(1);
	return (1);
}

int		color_parser(t_map *map)
{
	ft_array_len(map->sline) != 2 ? error(1) : 0;
	if (!map->flags.spr && !ft_strncmp(map->sline[0], "S", 1) &&
						(map->flags.spr = 1))
		map->texture.spr = ft_strdup(map->sline[1]);
	else if (!map->flags.fl && !ft_strncmp(map->sline[0], "F", 1) &&
												(map->flags.fl = 1))
	{
		!(map->f = ft_split(map->sline[1], ',')) || !chcolor(map->f) ?
																error(1) : 0;
		ft_array_len(map->f) == 3 ? map->texture.fl = ft_atoi(map->f[0]) << 16
						| ft_atoi(map->f[1]) << 8 | ft_atoi(map->f[2]) : 0;
	}
	else if (!map->flags.ceil && !ft_strncmp(map->sline[0], "C", 1) &&
												(map->flags.ceil = 1))
	{
		!(map->c = ft_split(map->sline[1], ',')) || !chcolor(map->c) ?
																error(1) : 0;
		ft_array_len(map->c) == 3 ? map->texture.ceil = ft_atoi(map->c[0])
				<< 16 | ft_atoi(map->c[1]) << 8 | ft_atoi(map->c[2]) : 0;
	}
	else
		return (0);
	return (1);
}

int		parser(char fd, t_map *map)
{
	while ((get_next_line(fd, &map->line)) > 0)
	{
		if (!(map->sline = ft_split(map->line, ' ')))
			return (0);
		if (*map->sline)
		{
			if (ft_strrncmp(map->sline[0], "111", 3) == 0)
				break ;
			if (ft_strchr(map->sline[0], 'R') ||
				ft_strchr(map->sline[0], 'O') || ft_strchr(map->sline[0], 'E'))
			{
				if (!(resolution_direction(map)))
					return (0);
			}
			else
			{
				if (!(color_parser(map)))
					return (0);
			}
		}
		free(map->line);
		ft_free_array(map->sline);
	}
	// ft_putendl_fd(map->line, 1);
	return (1);
}

int		main(int argc, char **argv)
{
	t_map	*map;
	int		fd;

	if (argc != 2 || !(map = (t_map*)ft_calloc(1 + 1, sizeof(t_map))) ||
								(fd = open(argv[1], O_RDONLY)) == -1)
		return (0);
	if (!(parser(fd, map)))
		error(1);
	if (!(map->x && map->y && map->flags.no && map->flags.so &&
				map->flags.we && map->flags.ea && map->flags.spr &&
				map->flags.fl && map->flags.ceil))
		error(1);
	if (close(fd) == -1)
		return (0);

	ft_putnbr_fd(map->x, 1);
	ft_putnbr_fd(map->y, 1);

	ft_putendl_fd(map->texture.no, 1);
	ft_putendl_fd(map->texture.so, 1);
	ft_putendl_fd(map->texture.we, 1);
	ft_putendl_fd(map->texture.ea, 1);

	ft_putendl_fd(map->texture.spr, 1);
	ft_putnbr_fd(map->texture.fl, 1);
	ft_putnbr_fd(map->texture.ceil, 1);
	// free(map);
	while (1);
}
