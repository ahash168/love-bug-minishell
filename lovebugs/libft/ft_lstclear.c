/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:02:16 by ahashem           #+#    #+#             */
/*   Updated: 2023/11/12 19:33:12 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;
	t_list	*temp;

	list = *lst;
	temp = NULL;
	while (list)
	{
		temp = list->next;
		del(list->content);
		free(list);
		list = temp;
	}
	*lst = NULL;
}
