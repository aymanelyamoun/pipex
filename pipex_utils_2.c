/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 08:21:29 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/21 00:59:08 by ael-yamo         ###   ########.fr       */
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

void	cmds_fail_0(t_cmd *cmds, int i, int ignore, char *path)
{
	int	j;
	int	k;

	k = 0;
	while (k <= (i - ignore))
	{
		j = 0;
		while (cmds[k].cmd_args[j])
		{
			free(cmds[k].cmd_args[j]);
			j++;
		}
		if (cmds[k].cmd_path)
			free(cmds[k].cmd_path);
		free(cmds[k].cmd_args);
		k++;
	}
	free(cmds);
	free(path);
	exit(2);
}
