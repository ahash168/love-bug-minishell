/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:57:23 by ahashem           #+#    #+#             */
/*   Updated: 2023/11/12 19:33:29 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*first;
	size_t	count;

	count = ft_lstsize(lst);
	first = NULL;
	while (count--)
	{
		newlist = ft_lstnew(f(lst->content));
		if (newlist == NULL)
		{
			ft_lstdelone(newlist, del);
			return (first);
		}
		ft_lstadd_back(&first, newlist);
		newlist = newlist->next;
		lst = lst->next;
	}
	return (first);
}
