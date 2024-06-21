/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:24:14 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/21 23:21:47 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	decide_fd(int *infile_fd, int *outfile_fd, char **argv, char *outfile)
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
		ft_printf("%s: ", argv[1]);
		perror(NULL);
		if (pipe(infile_pipe) < 0)
			perror(NULL);
		close(infile_pipe[1]);
		*infile_fd = infile_pipe[0];
		*outfile_fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	}
	else
		*outfile_fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0000644);
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
	int		i;

	while (lst -> cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			if (dup2(lst -> pipe_0, 0) < 0 || dup2(lst -> pipe_1, 1) < 0)
				exit(1);
			close(lst -> pipe_0);
			execve(lst -> path, lst -> arg, env);
		}
		else if (pid > 0)
		{
			close(lst -> pipe_1);
			if (lst -> next -> cmd == NULL)
			{
				i = count_arg(lst);
				while (i-- > 0)
					wait(NULL);
			}
		}
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
		(*lst) = (*lst)-> next;
}

int	main(int argc, char **argv, char **env)
{
	int		infile_fd;
	int		outfile_fd;
	char	*outfile;
	t_cmd	*lst;

	lst = first_lst();
	outfile = argv[argc - 1];
	outfile_fd = -1;
	infile_fd = -1;
	if (argc == 1)
		exit(0);
	path_check(env, argv, argc);
	decide_fd(&infile_fd, &outfile_fd, argv, outfile);
	create_lst(argc, argv, env, &lst);
	create_pipe(&lst, infile_fd, outfile_fd);
	ft_to_first(&lst);
	ft_pipex(lst -> next, env);
	exit(0);
}
