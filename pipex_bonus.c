/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:49:43 by jade-haa          #+#    #+#             */
/*   Updated: 2023/12/22 12:11:54 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	***get_mid(int argc, char **full_path, char **argv, t_com commands)
{
	int		i;
	char	***mid;

	i = 0;
	mid = (char ***)malloc((argc - 3) * sizeof(char **));
	if (!mid)
		ft_free_3d(NULL, i, commands.first, full_path);
	while (i < argc - 4)
	{
		mid[i] = fit_command(argv[i + 2], full_path);
		if (!mid[i] || mid[i] == 0)
			ft_free_3d(mid, i, commands.first, full_path);
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

	i = 0;
	full_path = get_path(envp);
	mid = NULL;
	commands.first = fit_command(argv[2], full_path);
	if (!commands.first)
		ft_free_2d(commands.first, full_path, 1);
	if (i < argc - 4)
		mid = get_mid(argc, full_path, argv, commands);
	commands.last = fit_command(argv[argc - 2], full_path);
	ft_free_2d(full_path, NULL, 0);
	if (!commands.last)
		ft_free_3d(mid, i, commands.first, NULL);
	fork_childs(init_fd(argv, argc), commands, envp, mid);
	ft_free_3d(mid, i, commands.first, commands.last);
}

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
