/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 01:47:44 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/18 22:37:42 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static void	ft_strcat(char *s1, const char *s2)
{
	while (*s1)
		s1++;
	while (*s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = '\0';
}

char	*ft_strjoin_1(char const *s1, char const *s2)
{
	int		total_len;
	char	*allocat;

	if (!s1 || !s2)
		return (0);
	total_len = strlen(s1) + strlen(s2) + 1;
	allocat = (char *)malloc(total_len);
	if (!allocat)
		return (0);
	*allocat = '\0';
	ft_strcat(allocat, s1);
	ft_strcat(allocat, s2);
	return (allocat);
}
