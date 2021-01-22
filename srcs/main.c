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
    while (all.point.x < end_x)
    {
        while (all.point.y < end_y)
        {
            pixel_put(&all.img, all.point.y, all.point.x, all.map_color);
            all.point.y++;
        }
        all.point.y -= SCALE;
        all.point.x++;
    }
    end_x = (all.plr.x + 1) * SCALE;
    end_y = (all.plr.y +1) * SCALE;
    all.plr.x *= SCALE;
    all.plr.y *= SCALE;
    while (all.plr.x < end_x)
    {
        while (all.plr.y < end_y)
        {
            pixel_put(&all.img, all.plr.y, all.plr.x, all.plr.color);
            all.plr.y++;
        }
        all.plr.y -= SCALE;
        all.plr.x++;
    }
}

// void    scale_plr(t_all all)
// {
//     all.img.img = mlx_new_image(all.mlx, 1080, 720);
//     all.img.addr = mlx_get_data_addr(all.img.img, &all.img.bpp, &all.img.line_len, &all.img.endian);

//     int end_x = (all.plr.x + 1) * SCALE;
//     int end_y = (all.plr.y +1) * SCALE;
//     all.plr.x *= SCALE;
//     all.plr.y *= SCALE;
//     while (all.plr.x < end_x)
//     {
//         while (all.plr.y < end_y)
//         {
//             pixel_put(&all.img, all.plr.y, all.plr.x, all.plr.color);
//             all.plr.y++;
//         }
//         all.plr.y -= SCALE;
//         all.plr.x++;
//     }
//     mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);
// }

void	ft_cast_ray(t_all *all)
{
	t_plr	ray = all->plr; // задаем координаты луча равные координатам игрока

	while (all->map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
	{
		ray.x += cos(ray.dir);
		ray.y += sin(ray.dir);
		pixel_put(&all->img, ray.y, ray.x, 0x990099);
	}
}

void    draw_map(t_all *all)
{
    all->point.x = 0;
    all->point.y = 0;
    all->img.img = mlx_new_image(all->mlx, 1080, 720);
    all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.line_len, &all->img.endian);
    while (all->map[all->point.x])
    {
        // printf("%s\n", all->map[all->point.x]);
        all->point.y = 0;
        while (all->map[all->point.x][all->point.y])
        {
            // if (all->map[all->point.x][all->point.y] == 'N' ||
            //         all->map[all->point.x][all->point.y] == 'S' ||
            //         all->map[all->point.x][all->point.y] == 'W' ||
            //         all->map[all->point.x][all->point.y] == 'E')
            // {
            //     all->plr.x = all->point.x;
            //     all->plr.y = all->point.y;
            //     // scale_plr(*all);
            // }
            if (all->map[all->point.x][all->point.y] == '1')
                scale_map(*all);
            all->point.y++;
        }
        all->point.x++;
        ft_cast_ray(all);
    }
    mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
}

// int     key_hook(int keycode, t_all *all)
// {
//     if (keycode == 53)
//     {
//         mlx_destroy_window(all->mlx, all->win);
//         exit(0);
//     }
//     if (keycode == 13)
//     {
//         all->plr.x--;
//         draw_map(all);
//         // scale_plr(*all);
//     }
//     if (keycode == 0)
//     {
//         all->plr.y--;
//         draw_map(all);
//         // scale_plr(*all);
//     }
//     if (keycode == 1)
//     {
//         all->plr.x++;
//         draw_map(all);
//         // scale_plr(*all);
//     }
//     if (keycode == 2)
//     {
//         all->plr.y++;
//         draw_map(all);
//         // scale_plr(*all);
//     }
//     printf("%d\n", keycode);
//     return (0);
// }

int     key_press(int keycode, t_all *all)
{
    if (keycode == 53)
    {
        mlx_destroy_window(all->mlx, all->win);
        exit(0);
    }
    if (keycode == 13)
    {
        all->plr.x--;
        // all->plr.y -= sin(all->plr.dir);
        // all->plr.x -= cos(all->plr.dir);
    }
    if (keycode == 0)
    {
        all->plr.y--;
    }
    if (keycode == 1)
    {
        all->plr.x++;
    }
    if (keycode == 2)
    {
        all->plr.y++;
    }
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
    // mlx_key_hook(all->win, key_hook, all);
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
                all->plr.x = i;
                all->plr.y = j;
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
