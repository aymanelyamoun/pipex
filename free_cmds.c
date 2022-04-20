/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 06:25:11 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/20 06:25:12 by ael-yamo         ###   ########.fr       */
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
#include "get_next_line/get_next_line.h"

void	free_cmds(t_cmd *cmds, int ignore, t_main_args args)
{
	int	i;
	int	j;

	i = 0;
	while (i < args.argc - (ignore + 1))
	{
		j = 0;
		while (cmds[i].cmd_args[j] != NULL)
		{
			free(cmds[i].cmd_args[j]);
			j++;
		}
		free(cmds[i].cmd_args);
		free(cmds[i].cmd_path);
		i++;
	}
	free(cmds);
}
