#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"
#include <stdlib.h>

char *get_path(char **envp)
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
	}
	free(arr);
}

static char	*join_cmd(char *path, char *cmd)
{
	char	*cmd_path;
	char	*to_free;

	cmd_path = ft_strjoin("/", cmd);
	to_free = cmd_path;
	cmd_path = ft_strjoin(path, cmd_path);
	free(to_free);
	return(cmd_path);
}
#include <string.h>
char	*get_cmd_path(char *path, char *cmd)
{
	int		i;
	char	**paths;
	char	*cmd_path;

	i = 2;
	if (access(cmd, F_OK | X_OK) == 0)
			return(cmd);
	paths = ft_split(path, ':');
	while (paths[i - 2] != NULL)
	{
		cmd_path = join_cmd(paths[i - 2], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free(paths);
			return(cmd_path);
		}
		i++;
	}
	free_arr(paths);
	cmd_not_found(cmd);
	return (0);
}
