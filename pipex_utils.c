/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 06:54:21 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/20 19:53:14 by ael-yamo         ###   ########.fr       */
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

void	ft_exit_with_err(int status, char *msg)
{
	perror(msg);
	exit(status);
}

void	cmd_not_found(char *msg)
{
	perror(msg);
	perror(" : cmmand not found");
}

t_main_args	set_args(int argc, char **argv, char **envp)
{
	t_main_args	args;

	args.argc = argc;
	args.argv = argv;
	args.envp = envp;
	return (args);
}

static void	get_cmds_u(t_cmd **cmds, t_main_args args, int ignore, char *path)
{
	int	i;

	i = ignore;
	while (i < args.argc - 1)
	{
		(*cmds)[i - ignore].cmd_args = ft_split(args.argv[i], ' ');
		if ((*cmds)[i - ignore].cmd_args == NULL)
			cmds_fail_0(*cmds, i, ignore, path);
		(*cmds)[i - ignore].cmd_path = get_cmd_path(path, \
		(*cmds)[i - ignore].cmd_args[0]);
		if ((*cmds)[i - ignore].cmd_path == NULL)
			cmds_fail_0(*cmds, i, ignore, path);
		(*cmds)[i - ignore].envp = args.envp;
		i++;
	}
}

t_cmd	*get_cmds(t_main_args args, int ignore)
{
	int		i;
	t_cmd	*cmds;
	char	*path;

	cmds = NULL;
	if (args.argc >= 5)
	{
		i = ignore;
		path = get_path(args.envp);
		if (path == NULL)
			ft_exit_with_err(3, "coudn't find the path of the cmd\n");
		cmds = malloc(sizeof(t_cmd) * (args.argc - (ignore + 1)));
		if (cmds == NULL)
		{
			free(path);
			exit(2);
		}
		get_cmds_u(&cmds, args, ignore, path);
		free(path);
	}
	return (cmds);
}
