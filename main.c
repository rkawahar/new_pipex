/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:24:14 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/24 17:45:29 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	decide_fd(int *infile_fd, int *outfile_fd, char **argv, char *outfile)
{
	int	infile_pipe[2];

	*infile_fd = open(argv[1], O_RDONLY);
	if (ft_strncmp(argv[1], "here_doc\0", 9) == 0)
	{
		*infile_fd = here_doc(argv[2]);
		*outfile_fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0000644);
	}
	else if (*infile_fd < 0)
	{
		write_error(argv[1]);
		if (pipe(infile_pipe) < 0)
			perror(NULL);
		close(infile_pipe[1]);
		*infile_fd = infile_pipe[0];
		*outfile_fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0000644);
		return (1);
	}
	else
		*outfile_fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	if (*outfile_fd < 0)
		write_error(outfile);
	return (0);
}

int	count_arg(t_cmd *lst)
{
	int	ans;

	ans = 0;
	ft_to_first(&lst);
	lst = lst -> next;
	while (lst -> cmd)
	{
		ans++;
		lst = lst -> next;
	}
	return (ans);
}

void	ft_pipex(t_cmd *lst, char **env)
{
	pid_t	pid;

	while (lst -> cmd)
	{
		if (ft_strncmp(lst -> path, "nothing\0", 9) == 0)
		{
			close(lst -> pipe_0);
			close(lst -> pipe_1);
			lst = lst -> next;
			continue ;
		}
		pid = fork();
		if (pid == 0)
			ft_children_prosess(lst, env);
		else if (pid > 0)
			ft_parent_prosses(lst);
		lst = lst -> next;
	}
}

void	create_pipe(t_cmd **lst, int infile_fd, int outfile_fd)
{
	int	pre_pipe[2];

	ft_to_first(lst);
	(*lst)-> pre -> pipe_1 = outfile_fd;
	(*lst)-> next -> pipe_0 = infile_fd;
	(*lst) = (*lst)-> next;
	while ((*lst)-> next -> cmd)
	{
		pipe(pre_pipe);
		(*lst)-> pipe_1 = pre_pipe[1];
		(*lst)-> next -> pipe_0 = pre_pipe[0];
		(*lst) = (*lst)-> next;
	}
}

int	main(int argc, char **argv, char **env)
{
	int		infile_fd;
	int		outfile_fd;
	char	*outfile;
	t_cmd	*lst;
	int		flg;

	lst = first_lst();
	outfile = argv[argc - 1];
	outfile_fd = -1;
	infile_fd = -1;
	if (argc == 1)
		exit(0);
	path_check(env, argv, argc);
	flg = decide_fd(&infile_fd, &outfile_fd, argv, outfile);
	create_lst(argc, argv, env, &lst);
	create_pipe(&lst, infile_fd, outfile_fd);
	ft_to_first(&lst);
	if (flg == 1)
	{
		free(lst -> next -> path);
		lst -> next -> path = "nothing\0";
	}
	ft_pipex(lst -> next, env);
	exit(0);
}
