/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:24:40 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/21 21:00:13 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			*cmd;
	char			*path;
	char			**arg;
	int				pipe_0;
	int				pipe_1;
	struct s_cmd	*pre;
}			t_cmd;

t_cmd	*first_lst(void);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		here_doc(char *eof);
size_t	ft_strlen(const char *s);
int		ft_printf(const char *str, ...);
int		ft_print_itoa(int num, int len);
int		ft_print_uint(unsigned int num, int len);
int		ft_to_hexaddress(unsigned long int num, int len);
int		ft_to_hex(unsigned int num, int len);
int		ft_to_upperhex(unsigned int num, int len);
void	path_check(char **env, char **argv, int argc);
void	create_lst(int argc, char **argv, char **env, t_cmd **lst);
void	absolute_path(t_cmd *lst, char **args);
void	relative_path(t_cmd *lst, char **args, char **env);
char	*ft_shift(char *str, int i);
char	*find_path(char **bin, char *cmd);
void	ft_to_first(t_cmd **lst);
char	**ft_split(char const *s, char c);
void	ft_free_bin(char **bin);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
// void	create_pipe(t_cmd **lst, int infile_fd, int outfile_fd);

#endif