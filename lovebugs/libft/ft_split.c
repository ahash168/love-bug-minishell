/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:02:39 by ahashem           #+#    #+#             */
/*   Updated: 2023/11/12 19:33:56 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordcount(const char *s, char c)
{
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			x++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (x);
}

char	*storeword(char const *s, char c)
{
	size_t	wordlen;
	size_t	i;
	size_t	j;
	char	*word;

	wordlen = 0;
	i = 0;
	j = 0;
	while (s[i] && s[i++] != c)
		wordlen++;
	word = malloc(sizeof(char) * (wordlen + 1));
	i = 0;
	while (s[i] && (i < wordlen))
		word[j++] = s[i++];
	word[j] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	count;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	count = wordcount(s, c);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	while (count--)
	{
		while (s[j] && s[j] == c)
			j++;
		arr[i] = storeword(s + j, c);
		j += ft_strlen(arr[i]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
