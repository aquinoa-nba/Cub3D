/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 19:34:47 by aquinoa           #+#    #+#             */
/*   Updated: 2020/11/13 13:59:44 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*begin_lst;

	if (!lst || !f)
		return (NULL);
	if (!(new_lst = ft_lstnew(f(lst->content))))
		return (NULL);
	begin_lst = new_lst;
	lst = lst->next;
	while (lst)
	{
		if (!(new_lst->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&begin_lst, del);
			return (NULL);
		}
		lst = lst->next;
		new_lst = new_lst->next;
	}
	return (begin_lst);
}
