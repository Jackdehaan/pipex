/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:43:42 by jade-haa          #+#    #+#             */
/*   Updated: 2023/12/21 16:43:44 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	*free_result(char **result, int elements)
{
	int	i;

	i = 0;
	while (i < elements)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static int	subcounter(char const *s, char c)
{
	int	count;
	int	inside_word;

	count = 0;
	inside_word = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (inside_word)
			{
				count++;
				inside_word = 0;
			}
		}
		else
		{
			if (!inside_word)
				inside_word = 1;
		}
		s++;
	}
	if (inside_word)
		count++;
	return (count);
}

char	**do_split(char **new_array, char const *s, char c)
{
	int	wordlen;
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (j < subcounter(s, c))
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		wordlen = 0;
		while (s[i + wordlen] != c && s[i + wordlen] != '\0')
			wordlen++;
		new_array[j] = malloc(wordlen + 1 * sizeof(char));
		if (!new_array[j])
			return (free_result(new_array, j));
		ft_strlcpy(new_array[j], &s[i], wordlen + 1);
		i += wordlen;
		j++;
	}
	new_array[j] = NULL;
	return (new_array);
}

char	**ft_split(char const *s, char c)
{
	char	**new_array;

	new_array = (char **)malloc((subcounter(s, c) + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	return (do_split(new_array, s, c));
}
