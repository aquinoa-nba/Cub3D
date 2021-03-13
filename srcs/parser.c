/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:16:40 by aquinoa           #+#    #+#             */
/*   Updated: 2021/03/13 16:54:20 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	pars_res(t_all *all)
{
	char	**s_line;
	int		res_h;
	int		res_w;
	int		i;

	mlx_get_screen_size(all->mlx, &res_w, &res_h);
	!ft_strrncmp(all->line, " ", 1) ? error("Space(s) after R config!") : 0;
	!(s_line = ft_split(all->line, ' ')) ? error("Memory error!") : 0;
	i = -1;
	while (s_line[++i])
		s_line[i][0] == '0' ? error("Wrong resolition!") : 0;
	if (!all->cflag.r && (all->cflag.r = 1) && ft_array_len(s_line) == 3 &&
			ft_isdigit_str(s_line[1]) && ft_isdigit_str(s_line[2]) &&
		!ft_strncmp(s_line[0], "R", ft_strlen(s_line[0])))
	{
		all->res_w = ft_atoi(s_line[1]);
		all->res_h = ft_atoi(s_line[2]);
		all->res0_w = all->res_w;
		all->res0_h = all->res_h;
		all->res_w > res_w || (ft_strlen(s_line[1])) > 4 ?
											all->res_w = res_w : 0;
		all->res_h > res_h || (ft_strlen(s_line[2])) > 4 ?
											all->res_h = res_h : 0;
	}
	else
	{
		ft_array_len(s_line) == 3 && (s_line[1][0] == '-' ||
			s_line[2][0] == '-') ? error("Negative resolution!") : 0;
		error("Incorrect resolution config!");
	}
	ft_free_array(s_line);
}

void	map_first_line(t_list **head, t_all *all)
{
	t_list		*new;

	!(new = ft_lstnew(ft_strdup(all->line))) ? error("Memory error!") : 0;
	!new->content ? error("Memory error!") : 0;
	ft_lstadd_back(head, new);
}

void	main_pars(t_all *all)
{
	if (*all->line == 'R')
		!all->cflag.r ? pars_res(all) : error("Duplicated R config!");
	else if (*all->line == 'N')
		!all->cflag.no ? pars_no(all) : error("Duplicated NO config!");
	else if (*all->line == 'S')
		pars_so_and_sprt(all);
	else if (*all->line == 'W')
		!all->cflag.we ? pars_we(all) : error("Duplicated WE config!");
	else if (*all->line == 'E')
		!all->cflag.ea ? pars_ea(all) : error("Duplicated EA config!");
	else if ((*all->line == 'F') ||
			(*all->line == 'C'))
		pars_floor_n_ceilling(all);
	else
		error("Incorrect config!");
}

void	parser(char fd, t_list **head, t_all *all)
{
	char	*line;
	int		gnl;

	while ((gnl = get_next_line(fd, &all->line)) > 0)
	{
		if (*all->line)
			if (ft_strncmp(line = ft_strtrim(all->line, " "), "1", 1) == 0)
			{
				free(line);
				map_first_line(head, all);
				break ;
			}
			else
			{
				free(line);
				!ft_strchr(TYPE, all->line[0]) ? error("Incorrect type!") : 0;
				line = all->line;
				main_pars(all);
				free(line);
			}
		else
			free(all->line);
	}
	gnl == -1 || gnl == 0 ? error("Map reading error!") : 0;
}
