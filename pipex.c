/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:08:37 by jade-haa          #+#    #+#             */
/*   Updated: 2023/11/20 15:16:48 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int main()
// {
//     // int pid = fork();
//     // if (pid == 0)
//     //     printf("Test");
//     // else
//     //     printf("%d", pid);
//     write(STDOUT_FILENO, "ls", 3);
// }

// int	main(int argc, char **envp)
// {
// 	char	*programPath;
// 	char	*args[] = {"ls", "-l", "/home/jade-haa/Desktop/", NULL};
// 	char	*envp[] = {NULL};

// 	programPath = "/bin/ls";
// 	// Execute the "ls" command
// 	if (execve(programPath, args, envp) == -1)
// 	{
// 		perror("execve");
// 		return (1);
// 	}
// 	// This code is only reached if execve fails
// 	printf("This line will not be reached if execve is successful.\n");
// 	return (0);
// }
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
	{
		flag[j] = command[i];
		i++;
		j++;
	}
	return (flag);
}

void	fork_process(char **envp, char **args)
{
	pid_t	pid;
	ssize_t	bytesread;
	int		pipefd[2];
	char	buffer[100];

	bytesread = 0;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		if (execve(args[0], args, &envp[1]) == -1)
			perror("execute program!!");
		// write(pipefd[1], "hel;o", 10);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		bytesread = read(pipefd[0], buffer, sizeof(buffer));
		close(pipefd[0]);
		buffer[bytesread] = '\0';
		printf("%s", buffer);
		wait(NULL);
	}
}
int	main(int argc, char **envp)
{
	pid_t	pid;
	char	*args[3];
	int		fd1;

	args[0] = ft_strjoin("/usr/bin/", envp[2]);
	args[1] = copy_flag(envp[2]);
	args[2] = NULL;
	fd1 = open("infile", O_RDWR | O_CREAT, 0777);
	// printf("%s %s %s\n", args[0], args[1], args[2]);
	dup2(fd1, 1);
	close(fd1);
	// printf("%s",copy_flag(envp[2]));
	// printf("%s\n", ft_strjoin("/bin/", envp[2]));
	// pft_strjoin("/bin/", envp[2]);
	fork_process(envp, args);
}
