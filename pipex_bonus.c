/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:49:43 by jade-haa          #+#    #+#             */
/*   Updated: 2024/02/28 13:47:21 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	***get_mid(int argc, char **full_path, char **argv, t_com commands)
{
	int		i;
	char	***mid;

	i = 0;
	if (!argv)
		ft_free_3d(NULL, commands.first, full_path, 1);
	mid = (char ***)malloc((argc - 3) * sizeof(char **));
	if (!mid)
		ft_free_3d(NULL, commands.first, full_path, 1);
	while (i < argc - 5)
	{
		mid[i] = fit_command(argv[i + 2], full_path);
		if (!mid[i] || mid[i] == 0)
			ft_free_3d(mid, commands.first, full_path, 1);
		i++;
	}
	mid[i] = NULL;
	return (mid);
}

int	main(int argc, char **argv, char **envp)
{
	char	**full_path;
	char	***mid;
	t_com	commands;
	int		i;
	int		status;

	status = 0;
	i = 0;
	if (argc < 5)
		exit(EXIT_FAILURE);
	full_path = get_path(envp);
	mid = NULL;
	commands.first = fit_command(argv[2], full_path);
	if (!commands.first)
		ft_free_2d(commands.first, full_path, 1);
	if (argc > 5)
		mid = get_mid(argc, full_path, argv, commands);
	commands.last = fit_command(argv[argc - 2], full_path);
	ft_free_2d(full_path, NULL, 0);
	if (!commands.last)
		ft_free_3d(mid, commands.first, NULL, 1);
	status = fork_childs(init_fd(argv, argc), commands, envp, mid);
	ft_free_3d(mid, commands.first, commands.last, 0);
	return (status);
}

// pid_last_child = fork_childs(init_fd(argv, argc), commands, envp, mid);
// waitpid(pid_last_child, &status, NULL);
// WIFEXITED
// int	main(int argc, char **argv, char **envp)
// {
// 	char	**full_path;
// 	char	***mid;
// 	t_com	commands;
// 	t_fd	fd;
// 	int		i;

// 	i = 0;
// 	fd = init_fd(fd, argv, argc);
// 	full_path = get_path(envp);
// 	commands.first = fit_command(argv[2], full_path);
// 	mid = (char ***)malloc((argc - 3) * sizeof(char **));
// 	if (!mid || !commands.first)
// 		ft_free_2d(commands.first, full_path, 1);
// 	while (i < argc - 4)
// 	{
// 		mid[i] = fit_command(argv[i + 2], full_path);
// 		if (!mid[i] || mid[i] == 0)
// 			ft_free_3d(mid, i, commands.first, full_path);
// 		i++;
// 	}
// 	mid[i] = NULL;
// 	commands.last = fit_command(argv[argc - 2], full_path);
// 	ft_free_2d(full_path, NULL, 0);
// 	if (!commands.last)
// 		ft_free_3d(mid, i, commands.first, NULL);
// 	fork_childs(fd, commands, envp, mid);
// 	ft_free_3d(mid, i, commands.first, commands.last);
// }
