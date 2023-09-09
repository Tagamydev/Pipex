/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:43:05 by samusanc          #+#    #+#             */
/*   Updated: 2023/09/09 21:51:06 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <pipex.h>

void	*ft_free2(void **str)
{
	if (!str)
		return (NULL);
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

void	proof_start(int argc)
{
	if (argc <= 1 || argc == 2)
	{
		if (argc == 1)
		{
			ft_putstr_fd("pipex: r u shure u r ok?\n", STDERR_FILENO);
			exit(69);
		}
		else
		{
			ft_putstr_fd("pipex: syntax error near unexpected token `newline'\n", STDERR_FILENO);
			exit(258);
		}
	}
	return ;
}

int	fork_error(void)
{
	int	i;

	i = fork();
	if (i == -1)
	{
		perror("pipex");
		exit(-1);
	}
	return (i);
}

void	pipe_error(int pipes[2])
{
	if (pipe(pipes) == -1)
	{
		perror("pipex");
		exit(-1);
	}
}

int	ft_heredoc(char *eof)
{
	int		pid;
	int		pipes[2];
	int		status;
	char	*str;

	pid = fork_error();
	pipe_error(pipes);
	if (!pid)
	{
		ft_printf("> ");
		str = get_next_line(STDIN_FILENO);
		while (str && ft_strncmp(str, eof, ft_strlen(eof)))
		{
			write(pipes[1], str, ft_strlen(str));
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

int	ft_first_child(t_pipex *pipex)
{
	char *str;

	if (!ft_strncmp(pipex->argv[0], "here_doc", ft_strlen("here_doc") + 1))
	{
		pipex->here = 1;
		pipex->fd = ft_heredoc(pipex->argv[1]);
		return (0);
	}
	pipex->fd = open(pipex->argv[0], O_RDONLY);
	if (pipex->fd == -1)
	{
		str = ft_strjoin("pipex: ", pipex->argv[0]);
		perror(str);
		ft_free2((void **)&str);
	}
	return (0);
}

int	is_address(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' && str[i])
		i++;
	while (str[i] && str[i] != ' ')
	{
		if (str[i++] == '/')
			return (1);
	}
	return (0);
}

char *cut_input(char *input)
{
	char	*str;
	char	*result;
	size_t	i;

	i = 0;
	while(input[i] == ' ' && input[i])
		i++;
	str = ft_strdup(input + i);
	i = 0;
	while (str[i] != ' ' && str[i])
		i++;
	str[i] = '\0';
	result = ft_strdup(str);
	ft_free2((void **)&str);
	return (result);
}

char	*get_address(char *input)
{
	char	*str;
	char	*str2;

	str = cut_input(input);
	if (access(str, X_OK) == -1)
	{
		str2 = ft_strjoin("pipex: ", str);
		perror(str2);
		ft_free2((void **)&str2);
		ft_free2((void **)&str);
		return (NULL);
	}
	return (str);
}

void	*print_cmd_not_found(char *cmd)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	errno = 127;
	return (NULL);
}

char	*split_paths_and_compare(char *path, char *input)
{
	char 	**split;
	char	*str;
	char	*first;
	size_t	i;

	i = 0;
	split = ft_split(path, ':');
	if (!split)
		return (get_address(input));
	first = cut_input(input);
	str = first;
	first = ft_strjoin("/", str);
	ft_free2((void **)&str);
	while (split[i])
	{
		str = ft_strjoin(split[i++], first);
		if (!access(str, X_OK))
			break;
		ft_free2((void **)&str);
	}
	if (!str)
		return (print_cmd_not_found(first + 1));
	ft_free2((void **)&first);
	return (str);
}

char	*get_path(char *input, char **envp, t_pipex *pipex)
{
	size_t	i;

	if (!envp || !*envp)
	{
		pipex->path = 0;
		return (get_address(input));
	}
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", ft_strlen("PATH=")))
			break;
		i++;
	}
	if (!envp[i])
	{
		pipex->path = 0;
		return (get_address(input));
	}
	return (split_paths_and_compare(envp[i] + 5, input));
}

char *get_cmd(char *input, char **envp, t_pipex *pipex)
{
	char *str;
	char *cmd;

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
	if(dup2(fd1, fd2) == -1)
	{
		perror("pipex: ");
		exit(errno);
	}
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
	if(execve(cmd, split, pipex->envp) == -1)
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

int	ft_last_child(t_pipex *pipex)
{
	if (!pipex->argv[pipex->i])
		exit(0);
	exit(wait_all_children(pipex->last_cmd));
	return (0);
}

int	ft_mid_child(t_pipex *pipex)
{
	char	*cmd;
	int		pid;

	if (pipex->fd == -1)
	{
		pipex->fd = dup(pipex->empty);
		return (0);
	}
	cmd = get_cmd(pipex->argv[pipex->i], pipex->envp, pipex);
	if (!cmd)
		return (0);
	execution(cmd, pipex, &pid);
	if (pipex->last_cmd)
		pipex->last_cmd = pid;
	return (0);
}

int	open_last(char *str)
{
	char *str1;
	int		fd;

	fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		str1 = ft_strjoin("pipex: ", str);
		perror(str1);
		ft_free2((void **)&str1);
	}
	return (fd);
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
