/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:11:05 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/18 22:35:06 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	detect_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	size_t	sjoin_len;
	size_t	index;

	sjoin_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	strjoin = (char *) malloc(sjoin_len);
	if (!strjoin)
		return (NULL);
	index = 0;
	while (*s1 != '\0')
		strjoin[index++] = *s1++;
	while (*s2 != '\0')
		strjoin[index++] = *s2++;
	strjoin[index] = '\0';
	return (strjoin);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	int		n;
	size_t	slen;

	slen = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (start > slen)
		return (ft_strdup(""));
	if (slen - start >= len)
		substr = (char *) malloc(len + 1);
	else
		substr = (char *) malloc(slen - start + 1);
	if (!substr)
		return (NULL);
	n = 0;
	while (start < slen && len > 0 && s[start + n] != '\0')
	{
		substr[n] = s[start + n];
		n++;
		len--;
	}
	substr[n] = '\0';
	return (substr);
}
