/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:07:24 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/18 12:44:29 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	error(char *error)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(error, 1);
	exit(0);
}

void	open_map(int fd, t_list **head)
{
	char	*line;
	int		gnl;
	t_list	*new;

	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (*line)
		{
			new = ft_lstnew(line);
			!new->content ? error("Memory error!") : 0;
			ft_lstadd_back(head, new);
		}
		else
			error("Invalid map!");
	}
	gnl == -1 ? error("Map reading error!!") : 0;
	new = ft_lstnew(line);
	!new->content ? error("Memory error!") : 0;
	ft_lstadd_back(head, new);
	close(fd);
}

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

void	check_save(char *arg, t_all *all)
{
	int		fd;

	ft_strrncmp(arg, "--save", 6) || ft_strlen(arg) != 6 ?
				error("Invalid argument for screenshot!") : 0;
	fd = open("screenshot.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	raycast(all);
	scrsht(fd, all);
	close(fd);
	exit(0);
}
