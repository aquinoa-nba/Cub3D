/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:16:40 by aquinoa           #+#    #+#             */
/*   Updated: 2021/02/18 11:39:58 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	pars_res(t_all *all)
{
	char	**s_line;
	int		res_h;
	int		res_w;

	mlx_get_screen_size(all->mlx, &res_w, &res_h);
	!(s_line = ft_split(all->line, ' ')) ? error("Memory error!") : 0;
	if (!all->cflag.r && (all->cflag.r = 1) && ft_array_len(s_line) == 3 &&
			ft_isdigit_str(s_line[1]) && ft_isdigit_str(s_line[2]) &&
		!ft_strncmp(s_line[0], "R", ft_strlen(s_line[0])))
	{
		all->res_w = ft_atoi(s_line[1]);
		all->res_h = ft_atoi(s_line[2]);
		all->res_w > res_w || (ft_strlen(s_line[1])) > 4 ?
											all->res_w = res_w : 0;
		all->res_h > res_h || (ft_strlen(s_line[2])) > 4 ?
											all->res_h = res_h : 0;
	}
	else
	{
		s_line[1][0] == '-' || s_line[2][0] == '-' ?
							error("Negative resolution!") : 0;
		error("Incorrect resolution config!");
	}
	ft_free_array(s_line);
}

void	map_first_line(t_list **head, t_all *all)
{
	t_list		*new;

	new = ft_lstnew(ft_strdup(all->line));
	!new->content ? error("Memory error!") : 0;
	ft_lstadd_back(head, new);
}

void	main_pars(t_all *all)
{
	*all->line == 'R' ? pars_res(all) : 0;
	*all->line == 'N' ? pars_no(all) : 0;
	*all->line == 'S' ? pars_so_and_sprt(all) : 0;
	*all->line == 'W' ? pars_we(all) : 0;
	*all->line == 'E' ? pars_ea(all) : 0;
	*all->line == 'F' || all->line[0] == 'C' ?
							pars_floor_n_ceilling(all) : 0;
}

void	parser(char fd, t_list **head, t_all *all)
{
	char	*line;
	int		gnl;

	while ((gnl = get_next_line(fd, &all->line)) > 0)
	{
		line = all->line;
		while (*all->line == ' ')
			all->line++;
		if (*all->line)
		{
			if (ft_strncmp(line, "1", 1) == 0)
			{
				all->line = line;
				map_first_line(head, all);
				break ;
			}
			!ft_strchr(TYPE, all->line[0]) ? error("Incorrect type!") : 0;
			main_pars(all);
		}
		free(line);
	}
	free(line);
	gnl == -1 ? error("Map reading error!") : 0;
}
