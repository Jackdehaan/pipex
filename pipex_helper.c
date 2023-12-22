/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:27:40 by jade-haa          #+#    #+#             */
/*   Updated: 2023/12/21 16:43:30 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(char *s)
{
	size_t	i;
	size_t	size;
	char	*emptyarray;

	i = 0;
	size = ft_strlen(s);
	emptyarray = malloc((size + 1) * sizeof(char));
	if (emptyarray == NULL)
		return (NULL);
	while (i < size)
	{
		emptyarray[i] = s[i];
		i++;
	}
	emptyarray[size] = '\0';
	return (emptyarray);
}

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (nmemb == 0 || size == 0)
	{
		return (malloc(1));
	}
	if (nmemb > SIZE_MAX / size)
	{
		return (NULL);
	}
	ptr = malloc(nmemb * size);
	if (ptr != NULL)
	{
		ft_bzero(ptr, nmemb * size);
	}
	return (ptr);
}

char	*ft_strnstr(char *big, char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		if (big[i] == little[j])
		{
			i++;
			++j;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
		if (little[j] == '\0' && i == 5)
			return ((char *)&big[i]);
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newarray;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	newarray = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = ft_strlen(s1);
	if (!newarray)
		return (NULL);
	ft_strlcpy(newarray, s1, i + 1);
	j = 0;
	while (s2[j] != '\0')
	{
		newarray[i] = s2[j];
		i++;
		j++;
	}
	newarray[i] = '\0';
	return (newarray);
}
