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

void	first_child(int **fd, int fd_input, int fd_output, t_cmd *cmds, int pipe_count, int i)
{
	dup2(fd_input, STDIN_FILENO);
	if (pipe_count == 1)
		dup2(fd[i][1], STDOUT_FILENO);
	else
		dup2(fd[i + 1][1], STDOUT_FILENO);
	close_pipes(fd, pipe_count);
	close(fd_output);
	close(fd_input);
	execve(cmds[i].cmd_path, cmds[i].cmd_args, cmds[i].envp);
	perror("something whent wrogn with execve\n");
}

void	other_childs(int **fd, int fd_input, int fd_output, t_cmd *cmds, int pipe_count, int i)
{
	dup2(fd[i][0], STDIN_FILENO);
	dup2(fd[i + 1][1], STDOUT_FILENO);
	close_pipes(fd, pipe_count);
	close(fd_output);
	close(fd_input);
	execve(cmds[i].cmd_path, cmds[i].cmd_args, cmds[i].envp);
	perror("something whent wrogn with execve\n");
}

void	last_child(int **fd, int fd_input, int fd_output, t_cmd *cmds, int pipe_count, int i)
{
	dup2(fd[pipe_count - 1][0], STDIN_FILENO);
	dup2(fd_output, STDOUT_FILENO);
	close_pipes(fd, pipe_count);
	close(fd_output);
	close(fd_input);
	execve(cmds[i].cmd_path, cmds[i].cmd_args, cmds[i].envp);
	perror("somthing whent wrogn with execve\n");
}

int	**generat_pipes(t_main_args args)
{
	int		cmd_num;
	int		i;
	int		*fd;
	int		**pipes;

	cmd_num = args.argc - 3 - 1;
	if (args.argc < 5)
		ft_exit_with_err(1, "not enough args for the program\n");
	pipes = malloc(cmd_num * sizeof(int));
	i = 0;
	while (i < cmd_num)
	{
		fd = malloc(sizeof(int) * 2);
		pipe(fd);
		pipes[i] = fd;
		i++;
	}
	return (pipes);
}

void	forked(int **pipes, t_cmd *cmd, t_main_args args, int infile, int outfile)
{
	int	i;
	int	id;
	int	pipe_num;

	pipe_num = args.argc - 4;
	i = 0;
	while (i <= pipe_num)
	{
		id = fork();
		if (id == 0)
		{
			if (i == 0)
				first_child(pipes, infile, outfile, cmd, pipe_num, i);
			else if (i == pipe_num)
				last_child(pipes, infile, outfile, cmd, pipe_num, i);
			else
				other_childs(pipes, infile, outfile, cmd, pipe_num, i);
		}
		i++;
	}
	close_pipes(pipes, pipe_num);
	close(infile);
	close(outfile);
}

void	pipex(int fd_input, int fd_output, t_main_args args)
{
	int		**pipes;
	int		id_1;
	t_cmd	*cmds;

	pipes = generat_pipes(args);
	cmds = get_cmds(args);
	id_1 = fork();
	if (id_1 == 0)
		forked(pipes, cmds, args, fd_input, fd_output);
	close_pipes(pipes, args.argc - 4);
	close(fd_output);
	close(fd_input);
	waitpid(id_1, 0, 0);
	while(waitpid(-1, 0, 0) >= 0);
}

t_main_args	set_args(int argc, char **argv, char **envp)
{
	t_main_args	args;

	args.argc = argc;
	args.argv = argv;
	args.envp = envp;
	return (args);
}

int main(int argc, char **argv, char **envp)
{
	int	fd_input;
	int	fd_output;
	t_main_args	args;

	args = set_args(argc, argv, envp);
	fd_input = open(argv[1], O_RDWR, 0777);
	fd_output = open(argv[argc - 1], O_RDWR | O_CREAT, 0777);
	pipex(fd_input, fd_output, args);
	close(fd_output);
	close(fd_input);
	exit(0);
}