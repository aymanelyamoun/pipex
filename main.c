#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>

void	pipex(int fd_input, int ft_output)
{
	int pipes[2];
	int	id_1;
	int	id_2;

	id_1 = fork();
	pipe(pipes);
	if (id_1 == 0)
		execute_cmd_1();
	wait();
	id_2 = fork();
	if (id_2 == 0)
		execute_cmd_2();
}

int main(int argc, char **argv)
{
	int	fd_input;
	int	fd_output;

	fd_input = open(argv[1], O_RDWR | O_CREAT);
	fd_output = open(argv[4], O_RDWR | O_CREAT);
	return (0);
}