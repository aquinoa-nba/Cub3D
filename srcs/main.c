/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:04:22 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/17 22:21:45 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_texture(t_all *all)
{
	all->txr[0].img = mlx_xpm_file_to_image(all->mlx, all->txrs.no,
								&all->rc.txr_width, &all->rc.txr_height);
	all->txr[0].addr = mlx_get_data_addr(all->txr[0].img, &all->txr[0].bpp,
								&all->txr[0].line_len, &all->txr[0].endian);
	all->txr[1].img = mlx_xpm_file_to_image(all->mlx, all->txrs.so,
								&all->rc.txr_width, &all->rc.txr_height);
	all->txr[1].addr = mlx_get_data_addr(all->txr[1].img, &all->txr[1].bpp,
								&all->txr[1].line_len, &all->txr[1].endian);
	all->txr[2].img = mlx_xpm_file_to_image(all->mlx, all->txrs.we,
								&all->rc.txr_width, &all->rc.txr_height);
	all->txr[2].addr = mlx_get_data_addr(all->txr[2].img, &all->txr[2].bpp,
								&all->txr[2].line_len, &all->txr[2].endian);
	all->txr[3].img = mlx_xpm_file_to_image(all->mlx, all->txrs.ea,
								&all->rc.txr_width, &all->rc.txr_height);
	all->txr[3].addr = mlx_get_data_addr(all->txr[3].img, &all->txr[3].bpp,
								&all->txr[3].line_len, &all->txr[3].endian);
}

void	orientation(int i, int j, t_all *all)
{
	double		view;

	view = (double)all->res_w / (double)all->res_h / 2.0;
	if (all->map[i][j] == 'N' || all->map[i][j] == 'S')
	{
		all->rc.p_dir_x = all->map[i][j] == 'N' ? -1 : 1;
		all->rc.p_dir_y = 0;
		all->rc.v_cam_x = 0;
		all->rc.v_cam_y = all->map[i][j] == 'N' ? view + 0.01 : -view - 0.01;
	}
	else
	{
		all->rc.p_dir_x = 0;
		all->rc.p_dir_y = all->map[i][j] == 'W' ? -1 : 1;
		all->rc.v_cam_x = all->map[i][j] == 'W' ? -view - 0.01 : view + 0.01;
		all->rc.v_cam_y = 0;
	}
	all->map[i][j] = '0';
}

void	player(t_all *all)
{
	int		i;
	int		j;

	i = -1;
	while (all->map[++i])
	{
		j = -1;
		while (all->map[i][++j])
			if (all->map[i][j] == 'N' || all->map[i][j] == 'S'
				|| all->map[i][j] == 'W' || all->map[i][j] == 'E')
			{
				all->rc.p_x = i + 0.5;
				all->rc.p_y = j + 0.5;
				orientation(i, j, all);
			}
	}
}

void	make_map(t_list *head, t_all *all)
{
	t_list	*tmp;
	int		i;

	tmp = head;
	if (!(all->map = ft_calloc((ft_lstsize(head) + 1), sizeof(char*))))
		error("Memory error!");
	i = 0;
	while (tmp)
	{
		all->map[i] = tmp->content;
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

	fd = 0;
	argc > 3 || (fd = open(argv[1], O_RDONLY)) == -1 ||
	ft_strrncmp(argv[1], ".cub", 4) ? error("Invalid argument!") : 0;
	!(all = (t_all*)malloc(sizeof(t_all))) ? error("Memory error!") : 0;
	parser(fd, &head, all);
	if (!(all->res_w && all->res_h && all->cflag.no &&
	all->cflag.so && all->cflag.we && all->cflag.ea &&
	all->cflag.spr && all->cflag.fl && all->cflag.ceil))
		error("Incorrect configuration!");
	open_map(fd, &head);
	make_map(head, all);
	player(all);
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, all->res_w, all->res_h, "cub3D");
	init_texture(all);
	if (argc == 3)
	{
		ft_strrncmp(argv[2], "--save", 6) || ft_strlen(argv[2]) != 6 ?
											error("Invalid argument!") : 0;
		fd = open("screenshot.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
		raycast(all);
		scrsht(fd, all);
		close(fd);
		exit(0);
	}
	all->rc.move_speed = 0.05;
	all->rc.rot_speed = 0.035;
	mlx_loop_hook(all->mlx, raycast, all);
	mlx_loop(all->mlx);
}
