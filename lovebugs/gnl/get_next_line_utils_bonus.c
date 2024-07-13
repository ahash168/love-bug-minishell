/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:46:34 by ahashem           #+#    #+#             */
/*   Updated: 2024/05/11 18:44:36 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s2 || !(*s2))
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i] && s2[i] != '\n')
		str[j++] = s2[i++];
	if (s2[i] == '\n')
		str[j++] = '\n';
	str[j] = '\0';
	if (s1)
		free(s1);
	return (str);
}
