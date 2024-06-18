/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:12:16 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/19 02:55:13 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_eof(char *eof)
{
	char	*ans;
	int		i;

	ans = (char *)malloc(ft_strlen(eof) + 3);
	if (ans == NULL)
		exit(1);
	ans[0] = '\n';
	i = 1;
	while (eof[i - 1])
	{
		ans[i] = eof[i - 1];
		i++;
	}
	ans[i++] = '\n';
	ans[i] = '\0';
	return (ans);
}

int	checker(char *str, char *eof)
{
	int		i;
	char	*new_eof;

	i = 0;
	new_eof = ft_eof(eof);
	if (ft_strncmp(str, eof, ft_strlen(eof)) == 0)
	{
		if (str[ft_strlen(eof)] == '\n')
		{
			free(new_eof);
			return (1);
		}
	}
	while (str[i])
	{
		if (ft_strncmp(&str[i], new_eof, ft_strlen(new_eof)) == 0)
		{
			free(new_eof);
			return (1);
		}
		i++;
	}
	free(new_eof);
	return (0);
}

char	*re_create(char *str, char tmp)
{
	char	*ans;
	int		i;

	ans = (char *)malloc(ft_strlen(str) + 2);
	if (ans == NULL)
		exit(1);
	i = -1;
	while (str[++i])
		ans[i] = str[i];
	ans[i] = tmp;
	ans[i + 1] = '\0';
	free(str);
	return (ans);
}

char	*pipex_gnl(char *eof)
{
	char	*ans;
	char	tmp;
	int		len;

	ans = (char *)malloc(1);
	if (ans == NULL)
		exit(1);
	ans[0] = '\0';
	write(1, "> ", 2);
	len = 0;
	while (1)
	{
		read(0, &tmp, 1);
		len++;
		ans = re_create(ans, tmp);
		if (checker(ans, eof) != 0)
			break ;
		if (tmp == '\n')
			write(1, "> ", 2);
	}
	ans[len - ft_strlen(eof) - 1] = '\0';
	return (ans);
}

int	here_doc(char *eof)
{
	int		pipe1[2];
	char	*str;

	str = pipex_gnl(eof);
	if (pipe(pipe1) < 0)
	{
		perror(NULL);
		exit(1);
	}
	write(pipe1[1], str, ft_strlen(str));
	close(pipe1[1]);
	free(str);
	return (pipe1[0]);
}
