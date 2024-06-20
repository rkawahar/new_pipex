/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:10:54 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/20 15:05:10 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(const char *s)
{
	int	ans;

	ans = 0;
	while (*s)
	{
		ans++;
		s++;
	}
	return (ans);
}

void	ft_to_first(t_cmd **lst)
{
	while ((*lst)-> cmd != NULL)
		(*lst) = (*lst)-> next;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ans;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ans = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (ans == NULL)
		return (NULL);
	ft_strlcpy(ans, s1, len1 + 1);
	i = 0;
	while (i < len2)
	{
		ans[len1 + i] = s2[i];
		i++;
	}
	ans[i + len1] = '\0';
	return (ans);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	dst = (char *)dst;
	len = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}
