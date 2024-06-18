/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 02:31:00 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/19 04:04:19 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_shift(char *str, int i)
{
	char	*ans;
	int		l;

	ans = (char *)malloc(ft_strlen(str) - i + 1);
	if (ans == NULL)
		exit(1);
	l = 0;
	while (str[i])
	{
		ans[l] = str[i];
		i++;
		l++;
	}
	ans[l] = '\0';
	free(str);
	return (ans);
}

void	ft_error(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			ft_printf("%s: No such file or directory\n", cmd);
			return ;
		}
		i++;
	}
	ft_printf("%s: command not found\n", cmd);
}

char	*find_path(char **bin, char *cmd)
{
	char	*tmp1;
	char	*tmp;
	int		i;

	i = 0;
	while (bin[i] != NULL)
	{
		tmp1 = ft_strjoin(bin[i], "/");
		tmp = ft_strjoin(tmp1, cmd);
		free(tmp1);
		if (tmp == NULL)
			exit(1);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	ft_error(cmd);
	return ("nothing");
}

void	ft_free_bin(char **bin)
{
	int	i;

	i = 0;
	while (bin[i])
		free(bin[i++]);
	free(bin);
}
