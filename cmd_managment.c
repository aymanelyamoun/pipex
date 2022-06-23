/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_managment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 02:38:06 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/22 00:17:40 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"
#include <stdlib.h>

char	*get_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path = ft_strdup(envp[i] + 5);
			return (path);
		}
		i++;
	}
	return (NULL);
}

static void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i] != NULL)
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

static char	*join_cmd(char *path, char *cmd)
{
	char	*cmd_path;
	char	*to_free;

	to_free = ft_strjoin_1("/", cmd);
	if (to_free == NULL)
		exit(2);
	cmd_path = ft_strjoin_1(path, to_free);
	if (cmd_path == NULL)
		exit(2);
	free(to_free);
	return (cmd_path);
}

char	*get_cmd_path(char *path, char *cmd)
{
	int		i;
	char	**paths;
	char	*cmd_path;

	i = 0;
	paths = ft_split(path, ':');
	if (paths == NULL)
		exit(2);
	while (paths[i] != NULL)
	{
		cmd_path = join_cmd(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free_arr(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_arr(paths);
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	cmd_not_found(cmd);
	return (NULL);
}
