/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 06:27:02 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/21 16:51:28 by ael-yamo         ###   ########.fr       */
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

void	ft_close(int fd1, int fd2, int fd3, int fd4)
{
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
}

void	first_child(int fd_input, int fd_output, int fd[2], t_cmd *cmds)
{
	dup2(fd_input, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	ft_close(fd[1], fd[0], fd_input, fd_output);
	execve(cmds[0].cmd_path, cmds[0].cmd_args, cmds[0].envp);
	perror("somthing whent wrogn with execve\n");
}

void	second_child(int fd_input, int fd_output, int fd[2], t_cmd *cmds)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_output, STDOUT_FILENO);
	ft_close(fd[1], fd[0], fd_input, fd_output);
	execve(cmds[1].cmd_path, cmds[1].cmd_args, cmds[1].envp);
	perror("somthing whent wrogn with execve\n");
}

void	pipex(int fd_input, int fd_output, t_main_args args, int ignore)
{
	int		fd[2];
	int		id_1;
	int		id_2;
	t_cmd	*cmds;

	pipe(fd);
	cmds = get_cmds(args, ignore);
	if (cmds == NULL)
		ft_exit_with_err(2, "couldn't generat the cmds\n");
	id_1 = fork();
	if (id_1 == -1)
		ft_exit_with_err(3, "somthing whent wrong with the forking : \n");
	if (id_1 == 0)
		first_child(fd_input, fd_output, fd, cmds);
	id_2 = fork();
	if (id_2 == -1)
		ft_exit_with_err(3, "somthing whent wrong with the forking : \n");
	if (id_2 == 0)
		second_child(fd_input, fd_output, fd, cmds);
	if (id_1 != 0 && id_2 != 0)
		free_cmds(cmds, ignore, args);
	close(fd[0]);
	close(fd[1]);
	waitpid(id_1, 0, 0);
	waitpid(id_2, 0, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int			fd_input;
	int			fd_output;
	t_main_args	args;

	args = set_args(argc, argv, envp);
	fd_input = open(argv[1], O_RDONLY, 0777);
	if (fd_input == -1)
		exit (2);

	fd_output = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_output == -1)
		exit (2);
	pipex(fd_input, fd_output, args, 2);
	close(fd_output);
	close(fd_input);
	exit(0);
}
