/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:23:21 by nzharkev          #+#    #+#             */
/*   Updated: 2024/05/16 10:59:07 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_l;
	t_list	*new_n;
	void	*set;

	if (!lst || !f || !del)
		return (NULL);
	new_l = NULL;
	while (lst)
	{
		set = f(lst->content);
		new_n = ft_lstnew(set);
		if (!new_n)
		{
			del(set);
			ft_lstclear(&new_l, (*del));
			return (new_l);
		}
		ft_lstadd_back(&new_l, new_n);
		lst = lst->next;
	}
	return (new_l);
}
