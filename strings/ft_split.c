/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:13:18 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/15 03:47:18 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

static int	ft_word_count(char const *s, char c)
{
	int	count;
	int	flag;

	flag = 1;
	count = 0;
	while (*s)
	{
		if (c == 0)
			return (1);
		if (*s != c)
		{
			if (flag)
				count++;
			flag = 0;
			s++;
		}
		if (*s == c)
		{
			s++;
			flag = 1;
		}
	}
	return (count);
}

static const char	*ft_word_size(char const *s, char c, int *len)
{
	int	i;

	i = 0;
	while (*s == c)
		s++;
	while (s[i] != c && s[i])
		i++;
	*len = i;
	return (&s[i]);
}

static char	**ft_free(char **str, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(str[j++]);
	free(str);
	return (0);
}

static void	ft_strncpy(char *dest, const char *s, int len)
{
	int	i;

	i = 0;
	while (i < len && *s)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
}

char	**ft_split(char const *s, char c)
{
	char		**arr;
	int			word_len;
	int			i;
	const char	*next;

	i = 0;
	if (!s)
		return (0);
	arr = (char **)malloc(((ft_word_count(s, c)) + 1) * sizeof(char *));
	if (!arr)
		return (0);
	next = s;
	while (i < (ft_word_count(s, c)))
	{
		next = ft_word_size(next, c, &word_len);
		arr[i] = (char *)malloc((word_len + 1) * sizeof(char));
		if (!arr[i])
			ft_free(arr, i);
		ft_strncpy(arr[i++], (next - word_len), word_len);
	}
	arr[i] = 0;
	return (arr);
}
