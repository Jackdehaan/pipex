/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fork_childs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:15:31 by jade-haa          #+#    #+#             */
/*   Updated: 2023/12/21 16:43:09 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_first(t_fd fd, char **first, char **envp)
{
	close(fd.pipes->curr_read);
	dup2(fd.infile_fd, STDIN_FILENO);
	dup2(fd.pipes->curr_write, STDOUT_FILENO);
	close(fd.pipes->curr_write);
	close(fd.infile_fd);
	execve(first[0], first, envp);
	perror("execve");
}

void	execute_mid(t_fd fd, char **mid, char **envp)
{
	dup2(fd.pipes->prev_read, STDIN_FILENO);
	dup2(fd.pipes->curr_write, STDOUT_FILENO);
	execve(mid[0], mid, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	execute_last(t_fd fd, char **second, char **envp)
{
	close(fd.pipes->curr_write);
	dup2(fd.pipes->curr_read, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
	execve(second[0], second, envp);
}

int	fork_childs(t_fd fd, t_com commands, char **envp, char ***mid)
{
	pid_t	child_pid;
	int		i;

	i = 0;
	fd.pipes = NULL;
	fd.pipes = init_pipes_fd(fd.pipes);
	child_pid = fork();
	if (handle_child_first(child_pid, fd, envp, commands.first) == 0
		|| fd.pipes == NULL)
		return (0);
	while (mid[i] && child_pid > 0)
	{
		fd.pipes = init_pipes_fd(fd.pipes);
		child_pid = fork();
		if (handle_child_mid(child_pid, fd, envp, mid[i]) == 0
			|| fd.pipes == NULL)
			return (0);
		i++;
	}
	child_pid = fork();
	if (handle_child_last(child_pid, fd, envp, commands.last) == 0
		|| fd.pipes == NULL)
		return (0);
	ft_free_pipes(fd.pipes);
	return (0);
}
