/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:04:42 by jade-haa          #+#    #+#             */
/*   Updated: 2023/11/20 11:28:22 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newarray;
	int		i;
	int		j;

	newarray = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	if (newarray == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		newarray[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (s2[i] != '\0' && s2[i] != ' ') //////anders
	{
		newarray[j] = s2[i];
		i++;
		j++;
	}
	newarray[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (newarray);
}
