/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:15:22 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/03 19:14:50 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/cub.h"

#define SCALE 10

void    pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}

void    scale_map(t_all all)
{
    int end_x = (all.point.x + 1) * SCALE;
    int end_y = (all.point.y + 1) * SCALE;
    all.point.x *= SCALE;
    all.point.y *= SCALE;
    while (all.point.y < end_y)
    {
        while (all.point.x < end_x)
        {
            pixel_put(&all.img, all.point.x, all.point.y, all.map_color);
            all.point.x++;
        }
        all.point.x -= SCALE;
        all.point.y++;
    }
}

void	ft_cast_ray(t_all *all)
{
	t_plr	ray;
    int     len = 0;

    ray = all->plr;
    ray.start = ray.dir - M_PI / 6;
    ray.end = ray.dir + M_PI / 6;
    while (ray.start <= ray.end)
    {
        ray.x = all->plr.x;
        ray.y = all->plr.y;
	    while (all->map.map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
	    {
	    	ray.x += cos(ray.start);
	    	ray.y += sin(ray.start);
	    	pixel_put(&all->img, ray.x, ray.y, all->plr.color);
            len++;
	    }
        ray.start += (M_PI / 3) / all->map.x;
    }
}

void    draw_mini_map(t_all *all)
{
    all->point.x = 0;
    all->point.y = 0;
    all->img.img = mlx_new_image(all->mlx, all->map.x, all->map.y);
    all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.line_len, &all->img.endian);
    while (all->map.map[all->point.y])
    {
        all->point.x = 0;
        while (all->map.map[all->point.y][all->point.x])
        {
            if (all->map.map[all->point.y][all->point.x] == '1')
                scale_map(*all);
            all->point.x++;
        }
        all->point.y++;
        ft_cast_ray(all);
    }
    mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
}

int     key_press(int keycode, t_all *all)
{
    if (keycode == 53)
    {
        mlx_destroy_window(all->mlx, all->win);
        exit(0);
    }
    if (keycode == 13)
    {
        all->plr.x += cos(all->plr.dir) * 3;
        all->plr.y += sin(all->plr.dir) * 3;
    }
    if (keycode == 1)
    {
        all->plr.x -= cos(all->plr.dir) * 3;
        all->plr.y -= sin(all->plr.dir) * 3;
    }
    if (keycode == 0)
    {
        all->plr.dir -= 0.1;
    }
    if (keycode == 2)
    {
        all->plr.dir += 0.1;
    }
    // printf("%d\n", keycode);
    draw_mini_map(all);
    return (0);
}

int		close_window(int keycode, t_all *all)
{
	exit(0);
}

void    make_window(t_all *all)
{
    int     i;

    i = 0;
    all->mlx = mlx_init();
    all->win = mlx_new_window(all->mlx, all->map.x, all->map.y, "figures");
    draw_mini_map(all);
    mlx_hook(all->win, 2, (1L<<0), key_press, all);
    mlx_hook(all->win, 17, (1L<<0),	close_window, all);
    mlx_loop(all->mlx);
}

int     make_map(t_list *head, t_all *all)
{
    t_list  *tmp;
    int     i;

    tmp = head;
    if (!(all->map.map = ft_calloc((ft_lstsize(head) + 1), sizeof(char*))))
        return (0);
    i = 0;
    while (tmp)
    {
        all->map.map[i] = tmp->content;
        i++;
        tmp = tmp->next;
    }
	validator(i - 1, all);
    return (1);
}

void	open_map(int fd, t_list **head)
{
    char    *line;
	int		gnl;

    while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (*line)
        	ft_lstadd_back(head, ft_lstnew(line));
		else
			error("Invalid map!");
	}
	gnl == -1 ? error("Map reading error!!") : 0;
    ft_lstadd_back(head, ft_lstnew(line));
    close(fd);
}

int     player(t_all *all)
{
    int     i;
    int     j;

    i = 0;
    while (all->map.map[i])
    {
        j = 0;
        while (all->map.map[i][j])
        {
            if (all->map.map[i][j] == 'N' || all->map.map[i][j] == 'S' ||
                all->map.map[i][j] == 'W' || all->map.map[i][j] == 'E')
            {
                all->plr.x = j * SCALE;
                all->plr.y = i * SCALE;
                all->plr.dir = all->map.map[i][j] == 'N' ? 3 * M_PI_2 :
                                all->map.map[i][j] == 'S' ? M_PI_2 :
                                all->map.map[i][j] == 'W' ? M_PI :
                                all->map.map[i][j] == 'E' ? 2 * M_PI : 0;
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int     main(int argc, char **argv)
{
	t_all   *all;
	t_list  *head;
	int		fd;

	argc != 2 || !(all = (t_all*)malloc(sizeof(t_all))) ||
	(fd = open(argv[1], O_RDONLY)) == -1 ? error("Invalid argument!") : 0;
	parser(fd, &head, all);

	// ft_putendl_fd(all->map.line, 1);
	// ft_putnbr_fd(all->map.x, 1);
	// ft_putnbr_fd(all->map.y, 1);

	// ft_putendl_fd(all->map.texture.no, 1);
	// ft_putendl_fd(all->map.texture.so, 1);
	// ft_putendl_fd(all->map.texture.we, 1);
	// ft_putendl_fd(all->map.texture.ea, 1);

	// ft_putendl_fd(all->map.texture.spr, 1);
	// ft_putnbr_fd(all->map.texture.fl, 1);
	// ft_putnbr_fd(all->map.texture.ceil, 1);

	if (!(all->map.x && all->map.y && all->map.flags.no && all->map.flags.so &&
				all->map.flags.we && all->map.flags.ea && all->map.flags.spr &&
				all->map.flags.fl && all->map.flags.ceil))
		error("Incorrect configuration!");

	all->plr.color = all->map.texture.fl;
	all->map_color = all->map.texture.ceil;
	open_map(fd, &head);
	if (!(make_map(head, all)))
		return (0);
	if (!(player(all)))
		return(0);
	make_window(all);
}
