/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:33:57 by jade-haa          #+#    #+#             */
/*   Updated: 2023/12/22 11:55:23 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_2d(char **string1, char **string2, int exit_int)
{
	int	i;

	i = 0;
	if (string1)
	{
		while (string1[i])
		{
			free(string1[i]);
			string1[i] = NULL;
			i++;
		}
		free(string1);
	}
	if (string2)
		ft_free_2d(string2, NULL, exit_int);
	if (exit_int == 1)
		exit(1);
}

void	ft_free_3d(char ***mid, int count, char **command, char **full)
{
	int	i;
	int	j;

	i = 0;
	if (mid)
	{
		while (i < count)
		{
			j = 0;
			while (j < 2)
			{
				free(mid[i][j]);
				j++;
			}
			free(mid[i]);
			i++;
		}
		free(mid);
	}
	if (command)
	{
		ft_free_2d(command, full, 0);
	}
	exit(1);
}

int	ft_free_pipes(t_pipe *pipes)
{
	free(pipes);
	return (0);
}
