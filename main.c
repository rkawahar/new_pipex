/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:24:14 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/20 20:57:03 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



void	decide_fd(int *infile_fd, int *outfile_fd, char **argv, char *outfile)
{
	int	infile_pipe[2];

	(void)infile_pipe;
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

void	ft_pipex(t_cmd *lst, char **env, int infile_fd, int outfile_fd)
{
	pid_t	pid;
	int		pp[2];

	pipe(pp);
	pid = fork();
	if (pid > 0)
	{
		ft_pipex(lst -> pre, env, pp[0], outfile_fd);
		wait(NULL);
	}
	else if (pid == 0)
	{
		if (dup2(infile_fd, 0) < 0 || dup2(pp[1], 1) < 0)
			exit(1);
		if (execve(lst -> path, lst -> arg, env) < 0)
			exit(1);
	}
	close(infile_fd);
	close(pp[1]);
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
