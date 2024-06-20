/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 02:00:57 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/20 20:53:00 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*first_lst(void)
{
	t_cmd	*nil;

	nil = (t_cmd *)malloc(sizeof(t_cmd));
	if (nil == NULL)
	{
		write(2, "malloc error", 13);
		exit(1);
	}
	nil -> next = nil;
	nil -> cmd = NULL;
	nil -> path = NULL;
	nil -> arg = NULL;
	// nil -> pipe_0 = -1;
	// nil -> pipe_1 = -1;
	nil -> pre = nil;
	return (nil);
}

void	ft_connect_nord(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = (*lst)-> next;
	(*lst)-> next = new;
	new -> next = tmp;
	tmp -> pre = new;
	new -> pre = (*lst);
}

void	ft_insert_info(t_cmd **lst, int argc, char **argv, char **env)
{
	int		i;
	char	**args;

	i = 2;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		i++;
	while (i < argc - 1)
	{
		(*lst) = (*lst)-> next;
		args = ft_split(argv[i], ' ');
		if (args == NULL)
			exit(1);
		if (access(args[0], F_OK) == 0)
			absolute_path(*lst, args);
		else
			relative_path(*lst, args, env);
		i++;
	}
	ft_to_first(lst);
}

void	create_lst(int argc, char **argv, char **env, t_cmd **lst)
{
	t_cmd	*tmp;
	int		num;

	if (ft_strncmp(argv[1], "fere_doc", 9) == 0)
		num = argc - 4;
	else
		num = argc - 3;
	while (0 < num)
	{
		tmp = first_lst();
		ft_connect_nord(lst, tmp);
		num--;
	}
	ft_insert_info(lst, argc, argv, env);
	(*lst) = (*lst)-> next -> next;
}

// void	create_pipe(t_cmd **lst, int infile_fd, int outfile_fd)
// {
// 	int	pre_pipe[2];
// 	int	i;

// 	i = 0;
// 	ft_to_first(lst);
// 	(*lst) = (*lst)-> next;
// 	while ((*lst)-> cmd)
// 	{
// 		i++;
// 		(*lst) = (*lst)-> next;
// 	}
// 	(*lst) = (*lst)-> next;
// 	while (i > 1)
// 	{
// 		pipe(pre_pipe);
// 		(*lst)-> pipe_1 = pre_pipe[1];
// 		(*lst)-> next -> pipe_0 = pre_pipe[0];
// 		(*lst) = (*lst)-> next;
// 		i--;
// 	}
// 	ft_to_first(lst);
// 	(*lst)-> pre -> pipe_1 = outfile_fd;
// 	(*lst)-> next -> pipe_0 = infile_fd;
// }
