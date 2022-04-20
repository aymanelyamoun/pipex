/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 06:24:45 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/20 07:08:19 by ael-yamo         ###   ########.fr       */
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

void	first_child_b(int **fd, t_data data, int pipe_count, int i)
{
	dup2(data.infile, STDIN_FILENO);
	if (pipe_count == 1)
		dup2(fd[i][1], STDOUT_FILENO);
	else
		dup2(fd[i + 1][1], STDOUT_FILENO);
	close_pipes(fd, pipe_count);
	close(data.outfile);
	close(data.infile);
	execve(data.cmd[i].cmd_path, data.cmd[i].cmd_args, data.cmd[i].envp);
	perror("something whent wrogn with execve 1\n");
}

void	other_childs_b(int **fd, t_data data, int pipe_count, int i)
{
	dup2(fd[i - 1][0], STDIN_FILENO);
	dup2(fd[i][1], STDOUT_FILENO);
	close_pipes(fd, pipe_count);
	close(data.outfile);
	close(data.infile);
	execve(data.cmd[i].cmd_path, data.cmd[i].cmd_args, data.cmd[i].envp);
	perror(data.cmd[i].cmd_args[0]);
	perror("something whent wrogn with execve 3\n");
}

void	last_child_b(int **fd, t_data data, int pipe_count, int i)
{
	dup2(fd[pipe_count - 1][0], STDIN_FILENO);
	dup2(data.outfile, STDOUT_FILENO);
	close_pipes(fd, pipe_count);
	close(data.outfile);
	close(data.infile);
	execve(data.cmd[i].cmd_path, data.cmd[i].cmd_args, data.cmd[i].envp);
	perror("somthing whent wrogn with execve 2\n");
}
