/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fork_childs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:15:31 by jade-haa          #+#    #+#             */
/*   Updated: 2024/02/28 16:05:06 by jade-haa         ###   ########.fr       */
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
	exit(EXIT_FAILURE);
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
	dup2(fd.outfile_fd, STDOUT_FILENO);
	execve(second[0], second, envp);
	perror("execve\n");
	exit(EXIT_FAILURE);
}

int	init_and_check(t_fd *fd, int *i, int *status)
{
	if (fd->infile_fd == -1 || fd->outfile_fd == -1)
		return (1);
	*status = 0;
	*i = 0;
	fd->pipes = NULL;
	fd->pipes = init_pipes_fd(fd->pipes);
	return (0);
}

int	fork_childs(t_fd fd, t_com commands, char **envp, char ***mid)
{
	pid_t	child_pid;
	int		i;
	int		status;

	i = 0;
	status = 0;
	if (init_and_check(&fd, &i, &status))
		return (1);
	child_pid = fork();
	if (handle_child_first(child_pid, fd, envp, commands.first) == 0)
		return (0);
	while (mid && mid[i] && child_pid > 0)
	{
		fd.pipes = init_pipes_fd(fd.pipes);
		child_pid = fork();
		if (handle_child_mid(child_pid, fd, envp, mid[i]) == 0
			|| fd.pipes == NULL)
			return (0);
		i++;
	}
	status = handle_child_last(child_pid, fd, envp, commands.last);
	if (fd.pipes == NULL)
		return (0);
	ft_free_pipes(fd.pipes);
	return (status);
}
