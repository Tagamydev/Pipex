/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_child_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:55:19 by samusanc          #+#    #+#             */
/*   Updated: 2023/09/11 13:02:38 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	ft_heredoc(char *eof)
{
	int		pid;
	int		pipes[2];
	int		status;
	char	*str;

	pipe_error(pipes);
	pid = fork_error();
	if (!pid)
	{
		ft_printf("> ");
		str = get_next_line(STDIN_FILENO);
		while (str && ft_strncmp(str, eof, ft_strlen(eof)))
		{
			ft_putstr_fd(str, pipes[1]);
			ft_free2((void **)&str);
			ft_printf("> ");
			str = get_next_line(STDIN_FILENO);
		}
		exit(1);
	}
	waitpid(pid, &status, 0);
	close(pipes[1]);
	return (pipes[0]);
}

void	child_exec(t_pipex *pipex, char *cmd, int pipes[2])
{
	char	**split;

	dup2_error(pipex->fd, STDIN_FILENO);
	close(pipex->fd);
	if (!pipex->last_cmd)
		dup2_error(pipes[1], STDOUT_FILENO);
	else
	{
		if (pipex->last_fd == -1)
			exit(1);
		dup2_error(pipex->last_fd, STDOUT_FILENO);
	}
	close(pipes[1]);
	split = ft_split(pipex->argv[pipex->i], ' ');
	if (!split)
		return ;
	if (execve(cmd, split, pipex->envp) == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror(cut_input(pipex->argv[pipex->i]));
		exit(-1);
	}
	exit(0);
}

void	execution(char *cmd, t_pipex *pipex, int *last)
{
	int		pid;
	int		pipes[2];

	pipe_error(pipes);
	pid = fork_error();
	if (!pid)
		child_exec(pipex, cmd, pipes);
	close(pipes[1]);
	close(pipex->fd);
	pipex->fd = pipes[0];
	*last = pid;
	return ;
}

void	wait_child(int pid)
{
	int	id;
	int	result;
	int	status;

	status = 0;
	id = waitpid(pid, &status, 0);
	result = WEXITSTATUS(status);
	while (1)
	{
		id = waitpid(-1, &status, 0);
		if (id < 0)
			break ;
	}
	exit(result);
}

int	wait_all_children(int last_pid)
{
	int	pid;
	int	status;

	pid = fork_error();
	if (!pid)
		wait_child(last_pid);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
