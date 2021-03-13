/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:04:22 by aquinoa           #+#    #+#             */
/*   Updated: 2021/03/13 17:21:51 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_texture(t_all *all)
{
	(all->txr[0].img = mlx_xpm_file_to_image(all->mlx, all->txrs.no,
								&all->rc.res[0].txr_width, &all->rc.res[0].txr_height)) ?
	all->txr[0].addr = mlx_get_data_addr(all->txr[0].img, &all->txr[0].bpp,
	&all->txr[0].line_len, &all->txr[0].endian) : error("Wrong NO texture!");
	(all->txr[1].img = mlx_xpm_file_to_image(all->mlx, all->txrs.so,
								&all->rc.res[1].txr_width, &all->rc.res[1].txr_height)) ?
	all->txr[1].addr = mlx_get_data_addr(all->txr[1].img, &all->txr[1].bpp,
	&all->txr[1].line_len, &all->txr[1].endian) : error("Wrong SO texture!");
	(all->txr[2].img = mlx_xpm_file_to_image(all->mlx, all->txrs.we,
								&all->rc.res[2].txr_width, &all->rc.res[2].txr_height)) ?
	all->txr[2].addr = mlx_get_data_addr(all->txr[2].img, &all->txr[2].bpp,
	&all->txr[2].line_len, &all->txr[2].endian) : error("Wrong WE texture!");
	(all->txr[3].img = mlx_xpm_file_to_image(all->mlx, all->txrs.ea,
								&all->rc.res[3].txr_width, &all->rc.res[3].txr_height)) ?
	all->txr[3].addr = mlx_get_data_addr(all->txr[3].img, &all->txr[3].bpp,
	&all->txr[3].line_len, &all->txr[3].endian) : error("Wrong EA texture!");
	(all->txr[4].img = mlx_xpm_file_to_image(all->mlx, all->txrs.spr,
								&all->sprt_w, &all->sprt_h)) ?
	all->txr[4].addr = mlx_get_data_addr(all->txr[4].img, &all->txr[4].bpp,
	&all->txr[4].line_len, &all->txr[4].endian) :
						error("Wrong Sprite texture!");
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
		check_save(argv[2], all);
	all->rc.move_speed = 0.05;
	all->rc.rot_speed = 0.035;
	mlx_hook(all->win, 2, 0, key_press, all);
	mlx_hook(all->win, 3, 0, key_unpress, all);
	mlx_hook(all->win, 17, 0, close_window, all);
	mlx_loop_hook(all->mlx, raycast, all);
	mlx_loop(all->mlx);
}
