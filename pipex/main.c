/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:43:05 by samusanc          #+#    #+#             */
/*   Updated: 2023/09/11 13:00:34 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	proof_start(argc);
	argv++;
	init_pipex(&pipex, argc, argv, envp);
	ft_first_child(&pipex);
	if (pipex.here)
		pipex.i += 1;
	pipex.last_fd = open_last(argv[argc - 2]);
	while (pipex.i < (size_t)(pipex.argc - 2))
	{
		if (pipex.i == (size_t)(pipex.argc - 3))
			pipex.last_cmd = 1;
		ft_mid_child(&pipex);
		pipex.i += 1;
	}
	ft_last_child(&pipex);
	return (pipex.last_cmd);
}

char	*get_cmd(char *input, char **envp, t_pipex *pipex)
{
	char	*str;
	char	*cmd;

	if (is_address(input))
		return (get_address(input));
	else
	{
		cmd = get_path(input, envp, pipex);
		if (!is_address(cmd) && !pipex->path && cmd)
		{
			str = ft_strjoin("./", cmd);
			ft_free2((void **)&cmd);
			cmd = str;
		}
		return (cmd);
	}
	return (NULL);
}

void	dup2_error(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("pipex: ");
		exit(errno);
	}
}

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int	pipes[2];

	pipex->i = 1;
	pipex->fd = 0;
	pipex->here = 0;
	pipex->last_cmd = 0;
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->path = 1;
	pipe_error(pipes);
	close(pipes[1]);
	pipex->empty = pipes[0];
}
