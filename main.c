/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:24:14 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/19 04:09:22 by rkawahar         ###   ########.fr       */
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

// void	lst_check(t_cmd **lst)
// {
// 	int	i;

// 	(*lst) = (*lst)-> next;
// 	while ((*lst)-> cmd)
// 	{
// 		ft_printf("---------------------------------------\n");
// 		ft_printf("cmd = %s\n", (*lst)-> cmd);
// 		ft_printf("path = %s\n", (*lst)-> path);
// 		i = 0;
// 		while ((*lst)-> arg[i])
// 		{
// 			ft_printf("arg[%d] = %s\n", i, (*lst)-> arg[i]);
// 			i++;
// 		}
// 		ft_printf("---------------------------------------\n");
// 		(*lst) = (*lst)-> next;
// 	}
// }

void	ft_pipex(lst, infile_fd, env, outfile_fd)
{
	
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
	// lst_check(&lst);
	ft_pipex(lst, infile_fd, env, outfile_fd);
	exit(0);
}
