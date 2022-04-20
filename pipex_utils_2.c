/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 08:21:29 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/20 08:23:51 by ael-yamo         ###   ########.fr       */
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

	j = 0;
	while (j < (i - ignore))
	{
		if (cmds[i - ignore].cmd_args[j])
			free(cmds[i - ignore].cmd_args[j]);
		if (cmds[i - ignore].cmd_path)
			free(cmds[i - ignore].cmd_path);
		j++;
	}
	free(cmds[i - ignore].cmd_args);
	free(cmds);
	free(path);
	exit(2);
}
