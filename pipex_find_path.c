/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_find_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:04:42 by jade-haa          #+#    #+#             */
/*   Updated: 2023/12/21 16:44:09 by jade-haa         ###   ########.fr       */
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
		exit(1);
	return (result_string);
}

char	*copy_flag(char *command)
{
	int		i;
	int		j;
	char	*flag;

	i = 0;
	while (command[i] && command[i] != ' ')
		i++;
	if (!command[i])
		return (NULL);
	i++;
	j = i;
	while (command[j])
		j++;
	flag = malloc(j * sizeof(char) + 1);
	if (!flag)
		return (NULL);
	j = 0;
	while (command[i])
		flag[j++] = command[i++];
	flag[j] = '\0';
	return (flag);
}

char	**set_result(char *str, char *flag)
{
	char	**result;

	result = (char **)malloc(3 * sizeof(char *));
	if (!result)
	{
		free(str);
		free(flag);
		return (NULL);
	}
	result[0] = ft_strdup(str);
	if (flag)
		result[1] = ft_strdup(flag);
	else
		result[1] = NULL;
	result[2] = NULL;
	free(str);
	free(flag);
	return (result);
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

char	**fit_command(char *argv, char **full_path)
{
	int		j;
	char	*str;
	size_t	len;
	char	*trimmed_command;
	char	*temp;

	len = length_command(argv);
	trimmed_command = (char *)malloc(len * sizeof(char));
	if (!trimmed_command)
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
			break ;
		free(str);
	}
	free(trimmed_command);
	return (set_result(str, copy_flag(argv)));
}
