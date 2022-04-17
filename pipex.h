#ifndef	PIPEX_H
#define PIPEX_H
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct	s_cmd
{
	char	*cmd_path;
	char	**cmd_args;
	char	**envp;
} t_cmd;

typedef struct	s_main_args
{
	int		argc;
	char	**argv;
	char	**envp;
}	t_main_args;

/************ STRING HANDLERS *************/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *str);

/************   PIPEX UTILS   *************/

void	ft_exit_with_err(int status, char *msg);
void	cmd_not_found(char *msg);
// t_data	*set_data(t_main_args args);

/************   CMD MANGMENT   *************/

char	*get_path(char **envp);
char	*get_cmd_path(char *path, char *cmd);
t_cmd	*get_cmds(t_main_args args);
void	cmd_not_found(char *msg);

#endif