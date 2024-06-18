/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:23:35 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/05 15:19:10 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	counter(char const *s, char c)
{
	size_t	ans;
	size_t	i;

	ans = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
				ans++;
		i++;
	}
	return (ans);
}

void	str_index_cpy(size_t start, size_t end, char const *s, char *ans)
{
	size_t	i;

	i = 0;
	while (start < end)
	{
		ans[i] = s[start];
		start++;
		i++;
	}
	ans[i] = '\0';
}

void	ft_free(char **s, size_t index)
{
	while (index >= 0)
	{
		free(s[index]);
		index--;
	}
}

int	split_str(char **ans, char const *s, char c)
{
	size_t	start;
	size_t	end;
	size_t	index;

	end = 0;
	index = 0;
	while (s[end])
	{
		if (s[end] == c)
			end++;
		else
		{
			start = end;
			while (s[end] && s[end] != c)
				end++;
			ans[index] = (char *)malloc(sizeof(char) * (end - start + 1));
			if (ans == NULL)
			{
				ft_free(ans, index - 1);
				return (1);
			}
			str_index_cpy(start, end, s, ans[index++]);
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	cnt;
	char	**ans;

	if (s == NULL)
		return (NULL);
	cnt = counter(s, c);
	ans = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (ans == NULL)
		return (NULL);
	ans[cnt] = NULL;
	if (split_str(ans, s, c))
	{
		free(ans);
		return (NULL);
	}
	return (ans);
}
