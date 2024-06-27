/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:49:15 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/27 17:17:22 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_error(char *str)
{
	ft_printf("%s: ", str);
	perror(NULL);
}

void	ft_children_prosess(t_cmd *lst, char **env)
{
	if (dup2(lst -> pipe_0, 0) < 0 || dup2(lst -> pipe_1, 1) < 0)
		exit(1);
	close(lst -> pipe_0);
	close(lst -> pipe_1);
	execve(lst -> path, lst -> arg, env);
}

void	ft_parent_prosses(t_cmd *lst)
{
	int	i;

	close(lst -> pipe_1);
	if (lst -> next -> cmd == NULL)
	{
		i = count_arg(lst);
		while (i-- > 0)
			wait(NULL);
	}
}

int	check_sl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
