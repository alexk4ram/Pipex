/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkaram <alkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:08:58 by alkaram           #+#    #+#             */
/*   Updated: 2024/06/12 15:13:37 by alkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	ft_error(char *error_message, int system_function);
void	child_process(char **argv, char **envp, int *fd);
void	parent_process(char **argv, char **envp, int *fd, pid_t pid);
void	execute(char *cmd, char **envp);
void	ft_free(char **s);
char	*get_env(char *name, char **env);
char	*get_path(char *cmd, char **env);
int		ft_strcmp(char *s1, char *s2);
int		main(int argc, char **argv, char **envp);
int		ft_skip(char *s);

#endif
