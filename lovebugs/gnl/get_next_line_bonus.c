/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:37:27 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/11 17:30:40 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_charcountchecker(int count, char *temp)
{
	if (count == 0)
		return (temp);
	else if (count < 0)
	{
		if (temp)
			free(temp);
		return (NULL);
	}
	return (0);
}

void	ft_buffmaker(char *buff)
{
	if (ft_strchr(buff, '\n'))
		ft_memmove(buff, ft_strchr(buff, '\n') + 1,
			ft_strlen(ft_strchr(buff, '\n') + 1) + 1);
	else
		buff[0] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buff[10240][BUFFER_SIZE + 1];
	char		*temp;
	int			count;

	if (fd < 0)
		return (NULL);
	temp = NULL;
	count = 0;
	while (temp == NULL || (temp && !ft_strchr(temp, '\n')))
	{
		if (buff[fd][0] == '\0')
		{
			count = read(fd, buff[fd], BUFFER_SIZE);
			if (count == 0 || count < 0)
				return (ft_charcountchecker(count, temp));
			buff[fd][count] = '\0';
		}
		temp = ft_strjoin_gnl(temp, buff[fd]);
		ft_buffmaker(buff[fd]);
	}
	return (temp);
}
