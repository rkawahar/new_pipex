/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 02:10:47 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/19 03:08:17 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	no_env(char **argv, int argc)
{
	int	i;

	if (ft_strncmp("here_doc\n", argv[1], 9))
		i = 2;
	else
		i = 3;
	while (i < argc - 1)
	{
		ft_printf("%s: No such file or directory\n", argv[i]);
		i++;
	}
}

void	path_check(char **env, char **argv, int argc)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			return ;
		i++;
	}
	no_env(argv, argc);
	exit(1);
}

void	absolute_path(t_cmd *lst, char **args)
{
	lst -> cmd = args[0];
	lst -> path = args[0];
	lst -> arg = args;
}

char	*ft_path(char *cmd, char **env)
{
	char	**bin;
	int		i;
	char	*ans;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	bin = ft_split(env[i], ':');
	if (bin == NULL)
		exit(1);
	bin[0] = ft_shift(bin[0], 5);
	ans = find_path(bin, cmd);
	ft_free_bin(bin);
	return (ans);
}

void	relative_path(t_cmd *lst, char **args, char **env)
{
	int	i;

	i = 0;
	lst -> arg = args;
	lst -> cmd = args[0];
	lst -> path = ft_path(lst -> cmd, env);
}
