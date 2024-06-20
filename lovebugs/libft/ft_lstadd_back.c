/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 08:31:58 by ahashem           #+#    #+#             */
/*   Updated: 2023/11/10 08:36:15 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*list;

	list = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		list = *lst;
		if (list == NULL)
			list->next = new;
		while (list->next)
			list = list->next;
		list->next = new;
	}
}
