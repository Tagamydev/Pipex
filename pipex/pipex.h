/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:21:36 by samusanc          #+#    #+#             */
/*   Updated: 2023/09/11 13:01:46 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# include <limits.h>
# include <libft.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/errno.h>

typedef struct s_pipex{
	size_t	i;
	int		fd;
	int		here;
	int		last_cmd;
	int		argc;
	int		empty;
	int		path;
	int		last_fd;
	char	**argv;
	char	**envp;
}				t_pipex;

void	*ft_free2(void **str);
void	proof_start(int argc);
int		fork_error(void);
void	pipe_error(int pipes[2]);
int		ft_heredoc(char *eof);
int		ft_first_child(t_pipex *pipex);
int		is_address(char *str);
char	*cut_input(char *input);
char	*get_address(char *input);
void	*print_cmd_not_found(char *cmd);
char	*split_paths_and_compare(char *path, char *input);
char	*get_path(char *input, char **envp, t_pipex *pipex);
char	*get_cmd(char *input, char **envp, t_pipex *pipex);
void	dup2_error(int fd1, int fd2);
void	child_exec(t_pipex *pipex, char *cmd, int pipes[2]);
void	execution(char *cmd, t_pipex *pipex, int *last);
void	wait_child(int pid);
int		wait_all_children(int last_pid);
int		ft_last_child(t_pipex *pipex);
int		ft_mid_child(t_pipex *pipex);
int		open_last(char *str);
void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
int		main(int argc, char **argv, char **envp);

#endif
