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

t_cmd	*get_cmds(t_main_args args, int ignore)
{
	int		i;
	t_cmd	*cmds;
	char	*path;

	cmds = NULL;
	if (args.argc >= 5)
	{
		i = ignore;
		path = get_path(args.envp);
		if (path == NULL)
			ft_exit_with_err(3, "coudn't find the path of the cmd\n");
		cmds = malloc(sizeof(t_cmd) * (args.argc - (ignore + 1)));
		while (i < args.argc - 1)
		{
			cmds[i - ignore].cmd_args = ft_split(args.argv[i], ' ');
			cmds[i - ignore].cmd_path = get_cmd_path(path, cmds[i - ignore].cmd_args[0]);
			cmds[i - ignore].envp = args.envp;
			i++;
		}
		free(path);
	}
	return (cmds);
}
