/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:12:12 by jade-haa          #+#    #+#             */
/*   Updated: 2024/02/28 14:16:53 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_fd	init_fd(char **argv, int argc)
{
	t_fd	fd;

	if (access(argv[1], F_OK) == -1 || access(argv[1], R_OK) == -1)
	{
		perror("command not found");
		fd.infile_fd = 0;
	}
	else
		fd.infile_fd = open(argv[1], O_RDONLY);
	if (access(argv[4], F_OK) == 0 && access(argv[4], W_OK) == -1)
	{
		perror("outfile");
		fd.outfile_fd = 0;
	}
	else
		fd.outfile_fd = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0664);
	return (fd);
}

int	length_2d(char **flag)
{
	int	i;

	i = 0;
	if (flag)
	{
		while (flag[i])
		{
			i++;
		}
	}
	i++;
	return (i);
}

char	**copy_flag(char *command)
{
	int		i;
	int		j;
	char	**flag;

	i = 0;
	while (command[i] && command[i] != ' ')
		i++;
	if (!command[i])
		return (NULL);
	i++;
	j = i;
	flag = ft_split(&command[j], ' ');
	return (flag);
}

char	**set_result(char **str, char **flag, char **trimmed_line)
{
	char	**result;
	int		i;

	i = 0;
	result = (char **)malloc((length_2d(flag) + 1) * sizeof(char *));
	free(*trimmed_line);
	if (!result)
	{
		free(*str);
		free(flag);
		return (NULL);
	}
	result[0] = ft_strdup(*str);
	while (flag && flag[i])
	{
		result[i + 1] = ft_strdup(flag[i]);
		i++;
	}
	if (!flag)
		result[1] = NULL;
	result[i + 1] = NULL;
	free(*str);
	ft_free_2d(flag, NULL, 0);
	return (result);
}
