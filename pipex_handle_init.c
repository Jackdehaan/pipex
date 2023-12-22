/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_handle_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:00:29 by jade-haa          #+#    #+#             */
/*   Updated: 2023/12/22 12:11:17 by jade-haa         ###   ########.fr       */
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
		ft_free_pipes(fd.pipes);
		return (0);
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
		ft_free_pipes(fd.pipes);
		return (0);
	}
	else
	{
		close(fd.pipes->curr_write);
		wait(NULL);
	}
	return (1);
}

int	handle_child_last(pid_t child_pid, t_fd fd, char **envp, char **command)
{
	if (child_pid < 0)
	{
		perror("fork");
		ft_free_pipes(fd.pipes);
		return (0);
	}
	else if (child_pid == 0)
	{
		execute_last(fd, command, envp);
		ft_free_pipes(fd.pipes);
		return (0);
	}
	else
	{
		close(fd.pipes->curr_write);
		wait(NULL);
	}
	return (1);
}

t_pipe	*init_pipes_fd(t_pipe *pipes)
{
	int	fd[2];

	if (pipes == NULL)
	{
		pipes = (t_pipe *)malloc(sizeof(t_pipe));
		if (pipes == NULL)
			return (NULL);
	}
	if (pipes->curr_write != 0)
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

t_fd	init_fd(char **argv, int argc)
{
	t_fd	fd;

	fd.infile_fd = open(argv[1], O_RDONLY);
	fd.outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd.infile_fd == -1 || fd.outfile_fd == -1)
		exit(1);
	return (fd);
}
