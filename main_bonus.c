#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"
#include <stdlib.h>
#include "get_next_line/get_next_line.h"

void	close_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	forked(int **pipes, t_data data, int ignore)
{
	int	i;
	int	id;
	int	pipe_num;

	pipe_num = data.args.argc - ignore - 2;
	i = 0;
	while (i <= pipe_num)
	{
		id = fork();
		if (id == 0)
		{
			if (i == 0)
				first_child_b(pipes, data, pipe_num, i);
			else if (i == pipe_num)
				last_child_b(pipes, data, pipe_num, i);
			else
				other_childs_b(pipes, data, pipe_num, i);
		}
		i++;
	}
	close_pipes(pipes, pipe_num);
	close(data.infile);
	close(data.outfile);
}

void	free_pipes(int	**pipes, t_main_args args, int	ignore)
{
	int	i;
	int	pipe_num;

	pipe_num = args.argc - ignore - 2;
	i = 0;
	while (i < pipe_num)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	pipex(int fd_input, int fd_output, t_main_args args, int ignore)
{
	int		**pipes;
	t_cmd	*cmds;
	t_data 	data;

	pipes = generat_pipes(args, ignore);
	cmds = get_cmds(args, ignore);
	data.args = args;
	data.infile = fd_input;
	data.outfile = fd_output;
	data.cmd = cmds;
	// id_1 = fork();
	// if (id_1 == 0)
	forked(pipes, data, ignore);
	close_pipes(pipes, args.argc - ignore - 2);
	close(fd_output);
	close(fd_input);
	// if (id_1 != 0)
	// {
	free_cmds(cmds, ignore, args);
	free_pipes(pipes, args, ignore);
	// }
	// waitpid(id_1, 0, 0);
	while(waitpid(-1, 0, 0) >= 0);
}

int main(int argc, char **argv, char **envp)
{
	int			fd_input;
	int			fd_output;
	t_main_args	args;
	args = set_args(argc, argv, envp);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		ft_heredoc(args);
	fd_output = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	fd_input = open(argv[1], O_RDONLY, 0777);
	pipex(fd_input, fd_output, args, 2);
	close(fd_output);
	close(fd_input);
	exit(0);
}
