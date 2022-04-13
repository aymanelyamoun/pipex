#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void	ft_close(int fd1, int fd2, int fd3, int fd4)
{
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
}

void	pipex(int fd_input, int fd_output)
{
	int fd[2];
	int	id_1;
	int	id_2;

	pipe(fd);
	id_1 = fork();
	if (id_1 == 0)
	{
		dup2(fd_input, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		ft_close(fd[1], fd[0], fd_input, fd_output);
		execlp("grep", "grep", "64",  NULL);
	}
	id_2 = fork();
	if (id_2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd_output, STDOUT_FILENO);
		ft_close(fd[1], fd[0], fd_input, fd_output);
		execlp("wc", "wc", "-l", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(id_2, 0, 0);
	while(waitpid(-1, 0, 0) >= 0);
}

int main(int argc, char **argv, char **envp)
{
	int	fd_input;
	int	fd_output;

	fd_input = open(argv[1], O_RDWR | O_CREAT);
	fd_output = open(argv[4], O_RDWR | O_CREAT);

	pipex(fd_input, fd_output);
	close(fd_output);
	close(fd_input);
	return (0);
}
