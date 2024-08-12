/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkaram <alkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:22:01 by alkaram           #+#    #+#             */
/*   Updated: 2024/06/12 17:04:05 by alkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *error_message, int system_function)
{
	if (!system_function)
		ft_putendl_fd(error_message, STDERR_FILENO);
	else
		perror(error_message);
	exit(1);
}

void	ft_free(char **s)
{
	size_t	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

char	*get_env(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**all_path;
	char	*path_part;
	char	**s_cmd;

	i = 0;
	all_path = ft_split(get_env("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (all_path[i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free(s_cmd);
			return (exec);
		}
		free(exec);
		i++;
	}
	ft_free(all_path);
	ft_free(s_cmd);
	return (cmd);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (!s1)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}
