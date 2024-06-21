/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:24:14 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/21 21:07:59 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	decide_fd(int *infile_fd, int *outfile_fd, char **argv, char *outfile)
{
	int	infile_pipe[2];

	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		*infile_fd = here_doc(argv[2]);
		*outfile_fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0000644);
	}
	else if (open(argv[1], O_RDONLY) == -1)
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
	{
		*infile_fd = open(argv[1], O_RDONLY);
		*outfile_fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	}
}

// void	ft_pipex(t_cmd *lst, char **env, int infile_fd, int outfile_fd)
// {

// }

void	create_pipe(t_cmd **lst, int infile_fd, int outfile_fd)
{
	int	pre_pipe[2];

	ft_to_first(lst);
	printf("cmd = %s\n", (*lst)-> cmd);
	(*lst)-> pre -> pipe_1 = outfile_fd;
	(*lst)-> next -> pipe_0 = infile_fd;
	printf("(*lst)-> pre -> pipe_1 = %d\n", (*lst)-> pre -> pipe_1);
	printf("(*lst)-> next -> pipe_0 = %d\n", (*lst)-> next -> pipe_0);
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
	ft_pipex(lst -> pre, env, infile_fd, outfile_fd);
	exit(0);
}
