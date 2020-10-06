/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:56:03 by arannara          #+#    #+#             */
/*   Updated: 2020/05/24 23:02:58 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	word_counter(char const *s, char c)
{
	size_t	i;
	size_t	amount;

	i = 0;
	amount = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			amount++;
		while (s[i] != c && s[i])
			i++;
	}
	return (amount);
}

static	void	*array_free(char **array, size_t j)
{
	while (j != 0)
		free(array[--j]);
	free(array);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	j;
	size_t	words;

	words = (!s) ? 0 : (word_counter(s, c) + 1);
	j = 0;
	if (words == 0 || !(array = (char**)malloc(words * sizeof(char*))))
		return (NULL);
	while (j < words - 1)
	{
		i = 0;
		while (*s == c && *s)
			s++;
		while (s[i] != c && s[i])
			i++;
		if (!(array[j] = (char*)malloc(i + 1)))
			return (array_free(array, j));
		i = 0;
		while (*s != c && *s)
			array[j][i++] = *s++;
		array[j++][i] = '\0';
	}
	array[j] = NULL;
	return (array);
}
