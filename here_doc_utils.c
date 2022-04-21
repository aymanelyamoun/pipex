/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 01:01:47 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/21 01:06:36 by ael-yamo         ###   ########.fr       */
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
		exit (2);
	free_cmds(cmds, ignore, args);
}
