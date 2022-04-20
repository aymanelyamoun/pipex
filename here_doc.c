/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 06:25:21 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/20 22:33:24by ael-yamo         ###   ########.fr       */
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

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	write_to_fd(int fd, char *str)
{
	int	status;

	status = write(fd, str, ft_strlen(str));
	if (str != NULL)
		free(str);
}

char	*call_gnl(void)
{
	char	*line;

	line = get_next_line(0);
	if (line == NULL)
		ft_exit_with_err(4, "some error with get next line\n");
	return (line);
}

char	*call_gnl_and_write_fd(int fd, char *line)
{
	char	*str;

	write(1, "heredoc > ", 10);
	write_to_fd(fd, line);
	str = call_gnl();
	return (str);
}
char	*call_strjoin(t_main_args args)
{
	char	*limiter;

	limiter = ft_strjoin_1(args.argv[2], "\n");
	if (limiter == NULL)
		exit(2);
	return (limiter);
}

void	free_l_l(char *line, char *limiter)
{
	if (line != NULL)
		free(line);
	if (limiter != NULL)
		free(limiter);
}

void	check_cmds(t_main_args args, int ignore)
{
	t_cmd	*cmds;

	cmds = get_cmds(args, ignore);
	if (cmds == NULL)
		exit(2);
	free_cmds(cmds, ignore, args);
}

void	ft_heredoc(t_main_args args)
{
	char	*line;
	int		fd;
	int		fd_out;
	char	*limiter;

	if (args.argc >= 6)
	{
		check_cmds(args, 3);
		fd = open("herdoc", O_CREAT | O_RDWR, 0777);
		fd_out = open(args.argv[args.argc - 1], O_CREAT | O_RDWR \
		| O_TRUNC, 0777);
		write(1, "heredoc > ", 10);
		line = call_gnl();
		limiter = call_strjoin(args);
		while ((line != NULL) && (ft_strcmp(limiter, line) != 0))
			line = call_gnl_and_write_fd(fd, line);
		free_l_l(line, limiter);
		close(fd);
		fd = open("herdoc", O_CREAT | O_RDWR, 0777);
		pipex(fd, fd_out, args, 3);
		unlink("herdoc");
		close(fd_out);
		exit(0);
	}
	ft_exit_with_err(1, "not enough argements for here_doc\n");
}
