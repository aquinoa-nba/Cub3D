/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:16:40 by aquinoa           #+#    #+#             */
/*   Updated: 2021/01/29 23:11:36 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		color_check(char **color)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (ft_atoi(color[i]) < 0 || ft_atoi(color[i]) > 255)
			return (0);
		i++;
	}
	return (1);
}

int		resolution_direction(char **line, t_map *map)
{
	static int		flag;

	if ((ft_strchr(line[0], 'R')) && (ft_array_len(line) != 3))
		return (0);
	else if ((ft_strchr(line[0], 'O') ||
						ft_strchr(line[0], 'E')) && (ft_array_len(line) != 2))
		return (0);
	if ((ft_array_len(line) == 3) && ++flag)
	{
		map->x = ft_atoi(line[1]);
		map->y = ft_atoi(line[2]);
	}
	else
	{
		if (!(ft_strncmp(line[0], "NO", 2)) && ++flag)
			map->texture.no = line[1];
		if (!(ft_strncmp(line[0], "SO", 2)) && ++flag)
			map->texture.so = line[1];
		if (!(ft_strncmp(line[0], "WE", 2)) && ++flag)
			map->texture.we = line[1];
		if (!(ft_strncmp(line[0], "EA", 2)) && ++flag)
			map->texture.ea = line[1];
	}
	return (flag <= 5 ? 1 : 0);
}

int		color_parser(char **line, t_map *map)
{
	char		**f;
	char		**c;

	if ((ft_array_len(line) != 2))
		return (0);
	if (!ft_strncmp(line[0], "S", 1) && !map->flags.flag_sprite)
	{
		map->texture.sprite = line[1];
		map->flags.flag_sprite = 1;
	}
	else if (!(ft_strncmp(line[0], "S", 1)))
	{
		return (0);
	}
	if (!(ft_strncmp(line[0], "F", 1)) && (map->flags.flag_floor == 0))
	{
		if (!(f = ft_split(line[1], ',')) || !(color_check(f)))
			return (0);
		((ft_array_len(f)) == 3) ? map->texture.floor = (ft_atoi(f[0]) << 16) |
									(ft_atoi(f[1]) << 8) | ft_atoi(f[2]) : 0;
		map->flags.flag_floor = 1;
	}
	else if (!(ft_strncmp(line[0], "F", 1)))
		return (0);
	if (!(ft_strncmp(line[0], "C", 1)) && (map->flags.flag_ceilling == 0))
	{
		if (!(c = ft_split(line[1], ',')) || !(color_check(c)))
			return (0);
		if ((ft_array_len(c)) == 3)
		{
			map->texture.ceilling = ((ft_atoi(c[0]) << 16) |
										(ft_atoi(c[1]) << 8) | ft_atoi(c[2]));
		}
		map->flags.flag_ceilling = 1;
	}
	else if (!(ft_strncmp(line[0], "C", 1)))
		return (0);
	return (1);
}

int		parser(char fd, t_map *map)
{
	char	*line;
	char	**split_line;
	int		i;

	i = 8;
	while (i && (get_next_line(fd, &line)) > 0)
	{
		if (!(split_line = ft_split(line, ' ')))
			return (0);
		if (*split_line && i--)
		{
			if (ft_strchr(split_line[0], 'R') ||
				ft_strchr(split_line[0], 'O') || ft_strchr(split_line[0], 'E'))
			{
				if (!(resolution_direction(split_line, map)))
					return (0);
			}
			else
			{
				if (!(color_parser(split_line, map)))
					return (0);
			}
		}
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_map	*map;
	int		fd;

	if (argc != 2 || !(map = (t_map*)ft_calloc(1, sizeof(t_map))) ||
								(fd = open(argv[1], O_RDONLY)) == -1)
		return (0);
	if (!(parser(fd, map)))
		error(1);
	if (!(map->x && map->y && map->texture.no && map->texture.so &&
				map->texture.we && map->texture.ea))
		error(1);
	if (close(fd) == -1)
		return (0);

	// ft_putnbr_fd(map->x, 1);
	// ft_putnbr_fd(map->y, 1);

	// ft_putstr_fd(map->texture.no, 1);
	// ft_putstr_fd(map->texture.so, 1);
	// ft_putstr_fd(map->texture.we, 1);
	// ft_putstr_fd(map->texture.ea, 1);

	// ft_putnbr_fd(map->texture.floor, 1);
	// ft_putnbr_fd(map->texture.ceilling, 1);
}
