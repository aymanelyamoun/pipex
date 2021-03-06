/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:11:17 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/18 22:36:31 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../pipex.h"

void	ft_free(char *ptr);
char	*ft_line(char **line, char **rem);
void	ft_read_file(int fd, char *buffer, char **rem, char **line);
char	*get_next_line(int fd);
int		detect_n(char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif