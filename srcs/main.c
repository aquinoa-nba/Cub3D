/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:04:22 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/07 13:41:47 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	orientation(int i, int j, t_all *all)
{
	if (all->map.map[i][j] == 'N' || all->map.map[i][j] == 'S')
	{
		all->rc.dirX = all->map.map[i][j] == 'N' ? -1 : 1;
		all->rc.dirY = 0;
		all->rc.planeX = 0;
		all->rc.planeY = all->map.map[i][j] == 'N' ? 0.66 : -0.66;
	}
	else
	{
		all->rc.dirX = 0;
		all->rc.dirY = all->map.map[i][j] == 'W' ? -1 : 1;
		all->rc.planeX = all->map.map[i][j] == 'W' ? -0.66 : 0.66;
		all->rc.planeY = 0;
	}
}

void	player(t_all *all)
{
	int		i;
	int		j;

	i = -1;
	while (all->map.map[++i])
	{
		j = -1;
		while (all->map.map[i][++j])
			if (all->map.map[i][j] == 'N' || all->map.map[i][j] == 'S'
				|| all->map.map[i][j] == 'W' || all->map.map[i][j] == 'E')
			{
				all->rc.posX = i + 0.5;
				all->rc.posY = j + 0.5;
				orientation(i, j, all);
			}
	}
}

void	make_map(t_list *head, t_all *all)
{
	t_list	*tmp;
	int		i;

	tmp = head;
	if (!(all->map.map = ft_calloc((ft_lstsize(head) + 1), sizeof(char*))))
		error("Memory error!");
	i = 0;
	while (tmp)
	{
		all->map.map[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	validator(i - 1, all);
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

int		main(int argc, char **argv)
{
	t_all	*all;
	t_list	*head;
	int		fd;

	argc != 2 || (fd = open(argv[1], O_RDONLY)) == -1 ?
										error("Invalid argument!") : 0;
	!(all = (t_all*)malloc(sizeof(t_all))) ? error("Memory error!") : 0;
	parser(fd, &head, all);
	if (!(all->map.x && all->map.y && all->map.flags.no && all->map.flags.so &&
				all->map.flags.we && all->map.flags.ea && all->map.flags.spr &&
				all->map.flags.fl && all->map.flags.ceil))
		error("Incorrect configuration!");
	open_map(fd, &head);
	make_map(head, all);
	player(all);
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, all->map.x, all->map.y, "cub3D");
	all->rc.moveSpeed = 0.05;
	all->rc.rotSpeed = 0.03;
	mlx_loop_hook(all->mlx, raycast, all);
	mlx_loop(all->mlx);
}
