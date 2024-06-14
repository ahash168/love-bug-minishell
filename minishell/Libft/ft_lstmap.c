/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <mgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:21:22 by mgordag           #+#    #+#             */
/*   Updated: 2022/10/18 11:21:23 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*new;

	nlst = NULL;
	while (lst)
	{
		new = ft_lstnew (f(lst->content));
		if (!new)
		{
			ft_lstclear(&lst, del);
			return (0);
		}
		ft_lstadd_back(&nlst, new);
		lst = lst->next;
	}
	return (nlst);
}
