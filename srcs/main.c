/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:15:22 by aquinoa           #+#    #+#             */
/*   Updated: 2021/01/22 23:58:08 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/cub.h"

#define SCALE 16

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
    // end_x = (all.plr.x + 1) * SCALE;
    // end_y = (all.plr.y +1) * SCALE;
    // all.plr.x *= SCALE;
    // all.plr.y *= SCALE;
    // while (all.plr.y < end_y)
    // {
    //     while (all.plr.x < end_x)
    //     {
    //         pixel_put(&all.img, all.plr.x, all.plr.y, all.plr.color);
    //         all.plr.x++;
    //     }
    //     all.plr.x -= SCALE;
    //     all.plr.y++;
    // }
}

void	ft_cast_ray(t_all *all)
{
	t_plr	ray;

    ray = all->plr;
    ray.start = ray.dir - M_PI / 6;
    ray.end = ray.dir + M_PI / 6;
    while (ray.start <= ray.end)
    {
        ray.x = all->plr.x;
        ray.y = all->plr.y;
	    while (all->map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
	    {
	    	ray.x += cos(ray.start);
	    	ray.y += sin(ray.start);
	    	pixel_put(&all->img, ray.x, ray.y, 0x990099);
	    }
        ray.start += (M_PI / 3) / 1080;
    }
}

void    draw_map(t_all *all)
{
    all->point.x = 0;
    all->point.y = 0;
    all->img.img = mlx_new_image(all->mlx, 1080, 720);
    all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.line_len, &all->img.endian);
    while (all->map[all->point.y])
    {
        all->point.x = 0;
        while (all->map[all->point.y][all->point.x])
        {
            if (all->map[all->point.y][all->point.x] == '1')
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
        // all->plr.y--;
        all->plr.x += cos(all->plr.dir) * 3;
        all->plr.y += sin(all->plr.dir) * 3;
    }
    if (keycode == 1)
    {
        // all->plr.y++;
        all->plr.x -= cos(all->plr.dir) * 3;
        all->plr.y -= sin(all->plr.dir) * 3;
    }
    if (keycode == 0)
    {
        // all->plr.x--;
        all->plr.dir -= 0.1;
    }
    if (keycode == 2)
    {
        // all->plr.x++;
        all->plr.dir += 0.1;
    }
    // printf("%d\n", keycode);
    draw_map(all);
    return (0);
}

void    make_window(t_all *all)
{
    int     i;

    i = 0;
    all->mlx = mlx_init();
    all->win = mlx_new_window(all->mlx, 1080, 720, "figures");
    draw_map(all);
    mlx_hook(all->win, 2, (1L<<0), key_press, all);
    mlx_loop(all->mlx);
}

int     make_map(t_list *head, t_all *all)
{
    t_list  *tmp;
    int     i;

    tmp = head;
    if (!(all->map = ft_calloc((ft_lstsize(head) + 1), sizeof(char*))))
        return (0);
    i = 0;
    while (tmp)
    {
        all->map[i] = tmp->content;
        i++;
        tmp = tmp->next;
    }
    return (1);
}

int     open_map(char *map, t_list **head, t_all *all)
{
    int     fd;
    char    *line;

    if ((fd = open(map, O_RDONLY)) == -1)
        return (0);
    while ((get_next_line(fd, &line)) > 0)
        ft_lstadd_back(head, ft_lstnew(line));
    ft_lstadd_back(head, ft_lstnew(line));
    close(fd);
    return (1);
}

int     player(t_all *all)
{
    int     i;
    int     j;

    i = 0;
    while (all->map[i])
    {
        j = 0;
        while (all->map[i][j])
        {
            if (all->map[i][j] == 'N' || all->map[i][j] == 'S' ||
                all->map[i][j] == 'W' || all->map[i][j] == 'E')
            {
                all->plr.x = j * SCALE;
                all->plr.y = i * SCALE;
                all->plr.dir = 3 * M_PI_2;
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

    if (argc != 2)
        return (0);
    if (!(all = (t_all*)malloc(sizeof(t_all))))
        return (0);
    all->plr.color = 0x00ff00;
    all->map_color = 0xff0000;
    if (!(open_map(argv[1], &head, all)))
        return (0);
    if (!(make_map(head, all)))
        return (0);
    if (!(player(all)))
        return(0);
    make_window(all);
}
