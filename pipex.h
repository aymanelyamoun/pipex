/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 06:50:43 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/21 01:07:13 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char	*cmd_path;
	char	**cmd_args;
	char	**envp;
}	t_cmd;

typedef struct s_main_args
{
	int		argc;
	char	**argv;
	char	**envp;
}	t_main_args;

typedef struct s_data
{
	t_cmd		*cmd;
	t_main_args	args;
	int			infile;
	int			outfile;
}	t_data;

/************ STRING HANDLERS *************/
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *src);
char		*ft_strjoin_1(char const *s1, char const *s2);
int			ft_strlen(const char *str);
int			ft_strcmp(char *s1, char *s2);

/************   PIPEX UTILS   *************/

void		pipex(int fd_input, int fd_output, t_main_args args, int ignore);
void		ft_exit_with_err(int status, char *msg);
void		cmd_not_found(char *msg);
t_main_args	set_args(int argc, char **argv, char **envp);
int			**generat_pipes(t_main_args args, int ignore);
void		close_pipes(int **pipes, int count);
void		free_cmds(t_cmd *cmds, int ignore, t_main_args args);
void		free_pipes(int **pipes, t_main_args args, int ignore);
void		fail_to_generat_pipes(int **pipes, int i);
// t_data	*set_data(t_main_args args);

/************   CMD MANGMENT   *************/

char		*get_path(char **envp);
char		*get_cmd_path(char *path, char *cmd);
t_cmd		*get_cmds(t_main_args args, int ignore);
void		cmd_not_found(char *msg);
void		cmds_fail(int **pipes, int ignore, t_main_args args);
void		cmds_fail_0(t_cmd *cmds, int i, int ignore, char *path);
void		check_cmds(t_main_args args, int ignore);

/***********     EXEC_CHILDS **************/

void		first_child_b(int **fd, t_data data, int pipe_count, int i);
void		other_childs_b(int **fd, t_data data, int pipe_count, int i);
void		last_child_b(int **fd, t_data data, int pipe_count, int i);
void		free_cmds(t_cmd *cmds, int ignore, t_main_args args);

/***********     HERE_DOC *****************/

char		*call_gnl_and_write_fd(int fd, char *line);
char		*call_strjoin(t_main_args args);
void		free_l_l(char *line, char *limiter);
void		check_cmds(t_main_args args, int ignore);
void		write_to_fd(int fd, char *str);
char		*call_gnl(void);
void		ft_heredoc(t_main_args args);

#endif