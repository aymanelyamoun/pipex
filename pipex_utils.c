#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"
#include <stdlib.h>

void	ft_exit_with_err(int status, char *msg)
{
	perror(msg);
	exit(status);
}

void	cmd_not_found(char *msg)
{
	perror(msg);
	perror(" : cmmand not found");
	exit(3);
}

t_cmd	*get_cmds(t_main_args args)
{
	int		i;
	t_cmd	*cmds;
	char	*path;

	cmds = NULL;
	if (args.argc >= 5)
	{
		i = 2;
		path = get_path(args.envp);
		if (path == NULL)
			ft_exit_with_err(3, "coudn't find the path of the cmd\n");
		cmds = malloc(sizeof(t_cmd) * args.argc - 3);
		while (i < args.argc - 1)
		{
			cmds[i - 2].cmd_args = ft_split(args.argv[i], ' ');
			cmds[i - 2].cmd_path = get_cmd_path(path, cmds[i - 2].cmd_args[0]);
			cmds[i - 2].envp = args.envp;
			i++;
		}
	}
	return (cmds);
}
