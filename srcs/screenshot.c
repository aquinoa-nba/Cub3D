/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:09:20 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/14 14:52:18 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	scrsht(int fd, t_all *all)
{
	unsigned int	file_size;
	short			reserved;
	unsigned int	pix_data_offset;
	unsigned int	header_size;
	short			planes;
	short			bpp;
	unsigned int	compress;
	unsigned int	image_size;
	int				x_pix_per_m;
	int				y_pix_per_m;
	unsigned int	ttl_colors;
	unsigned int	imp_colors;
	int				i;
	int				j;

	file_size = (all->res_w * all->res_h * 4) + 54;
	reserved = 0;
	pix_data_offset = 54;
	header_size = 40;
	planes = 1;
	bpp = 32;
	compress = 0;
	image_size = all->res_w * all->res_h;
	x_pix_per_m = 0;
	y_pix_per_m = 0;
	ttl_colors = 0;
	imp_colors = 0;
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write(fd, &reserved, 2);
	write(fd, &reserved, 2);
	write(fd, &pix_data_offset, 4);
	write(fd, &header_size, 4);
	write(fd, &all->res_w, 4);
	write(fd, &all->res_h, 4);
	write(fd, &planes, 2);
	write(fd, &bpp, 2);
	write(fd, &compress, 4);
	write(fd, &image_size, 4);
	write(fd, &x_pix_per_m, 4);
	write(fd, &y_pix_per_m, 4);
	write(fd, &ttl_colors, 4);
	write(fd, &imp_colors, 4);
	i = all->res_h + 1;
	j = all->res_h + 1;
	while (--i)
	{
			write(fd, all->img.addr + (i *  all->img.line_len), all->res_w * ( all->img.bpp / 8));
	}
}
