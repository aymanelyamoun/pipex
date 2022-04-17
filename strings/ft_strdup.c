/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:31:05 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/04/17 00:15:32 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../pipex.h"

char	*ft_strdup(const char *src)
{
	char	*dub;
	int		allocat;
	int		i;

	i = 0;
	allocat = ft_strlen(src) * sizeof(char);
	dub = (char *)malloc(allocat + 1);
	if (!dub)
		return (0);
	while (src[i])
	{
		dub[i] = src[i];
		i++;
	}
	dub[i] = '\0';
	return (dub);
}
