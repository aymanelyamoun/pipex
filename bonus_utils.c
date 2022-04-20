/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 07:21:42 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/20 08:21:49 by ael-yamo         ###   ########.fr       */
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

void	fail_to_generat_pipes(int **pipes, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(pipes[j]);
		j++;
	}
	free(pipes);
	exit (3);
}

void	free_pipes(int **pipes, t_main_args args, int ignore)
{
	int	i;
	int	pipe_num;

	pipe_num = args.argc - ignore - 2;
	i = 0;
	if (pipes != NULL)
	{
		while (i < pipe_num)
		{
			free(pipes[i]);
			i++;
		}
		free(pipes);
	}
}

void	cmds_fail(int **pipes, int ignore, t_main_args args)
{
	free_pipes(pipes, args, ignore);
	exit(2);
}

int	**generat_pipes(t_main_args args, int ignore)
{
	int		pipes_num;
	int		i;
	int		**pipes;

	pipes_num = args.argc - ignore - 2;
	if (args.argc < 5)
		ft_exit_with_err(1, "not enough args for the program\n");
	pipes = malloc(pipes_num * sizeof(int *));
	if (pipes == NULL)
		exit(3);
	i = 0;
	while (i < pipes_num)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipes == NULL)
			fail_to_generat_pipes(pipes, i);
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}
