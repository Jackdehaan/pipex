/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:05:03 by jade-haa          #+#    #+#             */
/*   Updated: 2023/12/22 12:11:36 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <aio.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct t_pipe
{
	int		curr_write;
	int		curr_read;
	int		prev_write;
	int		prev_read;
}			t_pipe;

typedef struct t_fd
{
	int		infile_fd;
	int		outfile_fd;
	t_pipe	*pipes;
}			t_fd;

typedef struct t_com
{
	char	**first;
	char	**last;

}			t_com;

char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(char *s);
char		*ft_strnstr(char *big, char *little, size_t len);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		**fit_command(char *argv, char **full_path);
char		*copy_flag(char *command);
char		**get_path(char **envp);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_strncmp(char *s1, char *s2, size_t n);
void		ft_free_mid(char ***mid, int mid_count);
void		ft_free_3d(char ***mid, int count, char **command, char **full);
void		ft_free_2d(char **string1, char **string2, int exit_int);
int			ft_free_pipes(t_pipe *pipes);
int			handle_child_first(pid_t child_pid, t_fd fd, char **envp,
				char **command);
int			handle_child_mid(pid_t child_pid, t_fd fd, char **envp,
				char **command);
int			handle_child_last(pid_t child_pid, t_fd fd, char **envp,
				char **command);
void		execute_first(t_fd fd, char **first, char **envp);
void		execute_mid(t_fd fd, char **first, char **envp);
void		execute_last(t_fd fd, char **first, char **envp);
t_fd		init_fd(char **argv, int argc);
t_pipe		*init_pipes_fd(t_pipe *pipes);
int			fork_childs(t_fd fd, t_com commands, char **envp, char ***mid);
void		execute_first(t_fd fd, char **first, char **envp);
void		execute_mid(t_fd fd, char **first, char **envp);
void		execute_last(t_fd fd, char **first, char **envp);
char		**ft_split(char const *s, char c);
char		*ft_strdup(char *s);

#endif