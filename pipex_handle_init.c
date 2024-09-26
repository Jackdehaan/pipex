/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_handle_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:00:29 by jade-haa          #+#    #+#             */
/*   Updated: 2024/02/28 14:14:15 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_child_first(pid_t child_pid, t_fd fd, char **envp, char **command)
{
	if (child_pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		execute_first(fd, command, envp);
	}
	else
	{
		close(fd.pipes->curr_write);
		wait(NULL);
	}
	return (1);
}

int	handle_child_mid(pid_t child_pid, t_fd fd, char **envp, char **command)
{
	if (child_pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		execute_mid(fd, command, envp);
	}
	else
	{
		close(fd.pipes->curr_write);
		wait(NULL);
	}
	return (1);
}

int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (127);
}

int	handle_child_last(pid_t child_pid, t_fd fd, char **envp, char **command)
{
	int	status;

	status = 0;
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("fork");
		return (0);
	}
	else if (child_pid == 0)
	{
		execute_last(fd, command, envp);
	}
	else
	{
		waitpid(child_pid, &status, 0);
		return (check_status(status));
	}
	return (1);
}

t_pipe	*init_pipes_fd(t_pipe *pipes)
{
	int	fd[2];

	if (pipes == NULL)
	{
		pipes = (t_pipe *)malloc(sizeof(t_pipe));
		pipes->curr_read = 0;
		pipes->curr_write = 0;
		if (pipes == NULL)
			return (NULL);
	}
	if (pipes->curr_write)
	{
		pipes->prev_read = pipes->curr_read;
		pipes->prev_write = pipes->curr_write;
	}
	if (pipe(fd) == -1)
	{
		if (pipes)
			ft_free_pipes(pipes);
		return (NULL);
	}
	pipes->curr_read = fd[0];
	pipes->curr_write = fd[1];
	return (pipes);
}
