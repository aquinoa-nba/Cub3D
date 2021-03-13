/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:09:20 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/23 03:48:37 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_value(t_all *all)
{
	all->scrsht.file_size = (all->res_w * all->res_h * 4) + 54;
	all->scrsht.reserved = 0;
	all->scrsht.pix_data_offset = 54;
	all->scrsht.header_size = 40;
	all->scrsht.planes = 1;
	all->scrsht.bpp = 32;
	all->scrsht.compress = 0;
	all->scrsht.image_size = all->res_w * all->res_h;
	all->scrsht.x_pix_per_m = 0;
	all->scrsht.y_pix_per_m = 0;
	all->scrsht.ttl_colors = 0;
	all->scrsht.imp_colors = 0;
}

void	scrsht(int fd, t_all *all)
{
	int		i;

	init_value(all);
	write(fd, "BM", 2);
	write(fd, &all->scrsht.file_size, 4);
	write(fd, &all->scrsht.reserved, 2);
	write(fd, &all->scrsht.reserved, 2);
	write(fd, &all->scrsht.pix_data_offset, 4);
	write(fd, &all->scrsht.header_size, 4);
	write(fd, &all->res_w, 4);
	write(fd, &all->res_h, 4);
	write(fd, &all->scrsht.planes, 2);
	write(fd, &all->scrsht.bpp, 2);
	write(fd, &all->scrsht.compress, 4);
	write(fd, &all->scrsht.image_size, 4);
	write(fd, &all->scrsht.x_pix_per_m, 4);
	write(fd, &all->scrsht.y_pix_per_m, 4);
	write(fd, &all->scrsht.ttl_colors, 4);
	write(fd, &all->scrsht.imp_colors, 4);
	i = all->res_h + 1;
	while (--i)
		write(fd, all->img.addr + (i * all->img.line_len),
											all->res_w * (all->img.bpp / 8));
}
