/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkaram <alkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:07:32 by alkaram           #+#    #+#             */
/*   Updated: 2024/06/12 17:04:19 by alkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int	in_file;

	close(fd[0]);
	in_file = open(argv[1], O_RDONLY, 0777);
	if (in_file == -1)
	{
		write(2, "pipex: ", 7);
		write(2, argv[1], ft_strlen(argv[1]));
		ft_error(": No such file or directory", 0);
	}
	if (dup2(fd[1], 1) == -1)
		ft_error("stdout dup2 error", 0);
	if (dup2(in_file, STDIN_FILENO) == -1)
		ft_error("1stdin dup2 error", 0);
	close(fd[1]);
	execute(argv[2], envp);
	close(in_file);
	exit(0);
}

void	parent_process(char **argv, char **envp, int *fd, pid_t pid)
{
	int	out_file;

	waitpid(pid, NULL, 0);
	close(fd[1]);
	out_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out_file == -1)
		ft_error("open error", 0);
	if (dup2(fd[0], 0) == -1)
		ft_error("2stdin dup2 error", 0);
	if (dup2(out_file, STDOUT_FILENO) == -1)
		ft_error("stdout dup2 error", 0);
	close(fd[0]);
	execute(argv[3], envp);
	close(out_file);
}

void	execute(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	if (cmd == NULL || ft_strlen(cmd) == 0)
	{
		ft_error("command error", 0);
		exit(1);
	}
	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], envp);
	if (!path)
	{
		ft_free(s_cmd);
		ft_error("path not found", 0);
		exit(127);
	}
	execve(path, s_cmd, envp);
	write(2, "pipex: ", 7);
	write(2, s_cmd[0], ft_strlen(s_cmd[0]));
	write(2, ": command not found\n", 20);
	exit(127);
}

int	ft_skip(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while ((s[i] != '\0') && (s[i] != ' '))
		i++;
	return (i);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		ft_error("argc error", 0);
	if (argv[1] == NULL || argv[4] == NULL || ft_skip(argv[1]) == 0
		|| ft_skip(argv[4]) == 0)
		ft_error("argv error", 0);
	if (argv[2] == NULL || argv[3] == NULL || ft_skip(argv[2]) == 0
		|| ft_skip(argv[3]) == 0)
		ft_error("argv error", 0);
	if (pipe(fd) == -1)
		ft_error("pipe error", 0);
	pid = fork();
	if (pid == -1)
		ft_error("fork error", 0);
	if (pid == 0)
		child_process(argv, envp, fd);
	else
		parent_process(argv, envp, fd, pid);
	return (0);
}
