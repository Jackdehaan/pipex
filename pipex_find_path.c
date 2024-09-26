/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_find_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:04:42 by jade-haa          #+#    #+#             */
/*   Updated: 2024/02/28 14:13:55 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	int		i;
	char	*path_string;
	char	**result_string;

	path_string = NULL;
	i = 0;
	while (!path_string)
	{
		path_string = ft_strnstr(envp[i], "PATH=", 5);
		i++;
	}
	result_string = ft_split(path_string, ':');
	if (!result_string)
		exit(EXIT_FAILURE);
	return (result_string);
}

int	length_command(char *command)
{
	int	i;

	i = 0;
	if (!command)
		return (0);
	while (command[i] && command[i] != ' ')
		i++;
	return (i + 1);
}

char	**empty_2d_array(char *argv)
{
	char	**result;

	(void)argv;
	result = (char **)malloc(2 * sizeof(char *));
	result[0] = ft_strdup("argv");
	result[1] = NULL;
	return (result);
}

int	init_fit_command(int *len, char *argv, char **trimmed_command)
{
	*len = length_command(argv);
	if (!argv || !argv[0])
		return (0);
	*trimmed_command = (char *)malloc(*len * sizeof(char));
	if (!trimmed_command)
		return (0);
	return (1);
}

char	**fit_command(char *argv, char **full_path)
{
	int		j;
	char	*str;
	int		len;
	char	*trimmed_command;
	char	*temp;

	trimmed_command = NULL;
	if (init_fit_command(&len, argv, &trimmed_command) == 0)
		return (NULL);
	ft_strlcpy(trimmed_command, argv, len);
	j = 0;
	while (full_path[j++])
	{
		temp = ft_strjoin(full_path[j], "/");
		str = ft_strjoin(temp, trimmed_command);
		if (!temp | !str)
			return (NULL);
		free(temp);
		if (access(str, X_OK) == 0)
			return (set_result(&str, copy_flag(argv), &trimmed_command));
		free(str);
	}
	free(trimmed_command);
	return (empty_2d_array(argv));
}
