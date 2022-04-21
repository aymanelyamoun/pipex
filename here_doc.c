/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 01:03:14 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/21 01:07:02 by ael-yamo         ###   ########.fr       */
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

void	ft_heredoc(t_main_args args)
{
	char	*line;
	int		fd;
	int		fd_out;
	char	*limiter;

	if (args.argc == 6)
	{
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
