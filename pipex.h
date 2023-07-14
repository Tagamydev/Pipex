/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:21:36 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/14 07:22:30 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# include <ft_error.h>
# include <ft_free.h>
# include <limits.h>
# include <libft.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_pipex{
	char	**paths;
	char	*command;
	char	**arg;
	int		pid1;
	int		pid2;
	int		pipe[2];
}		t_pipex;

void	ft_print_matrix(char **matrix);
void	ft_free_pipex(t_pipex *pipex);
char	*ft_prove_command(int *i, char **paths, char *cmd);
int		ft_exec_command(t_pipex *pipex);
char	**ft_get_paths(char **env);
char	*ft_get_cmd(char *cmd);
char	*ft_get_command(char **paths, char *command);
void	ft_first_child(t_pipex *pipex, char *infile, char *command);
void	ft_second_child(t_pipex *pipex, char *outfile, char *command);
int		main(int argc, char **argv, char **envp);

#endif
