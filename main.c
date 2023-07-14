/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:43:05 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/14 06:27:34 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <pipex.h>

//	gestion del input que el input exista, y que los argumentos existan
//	abrir el infile
//	abrir el outfile
//	crear el pipe
//	parseamos el path
//	hacemos el primer fork
//	ejecutamos el primer hijo
//		dup2 al pipe
//		cerramos el primer pipe
//		hacemos un dup2 al infile
//		obtenemos los argumentos del comando para el execv por medio de un split
//		obtenemos el comando
//		ejecutamos el commando antes asegurandonos que se pueda ejecutar
//	hacemos el segundo fork
//		hace lo mismo que el primer hijo
//	cerramos el pipe
//	esperamos a que el proceso 1 termine
//	esperamos a que el proceso 2 termine
//	terminamos la ejecucion
//
void	leaks()
{
	system("leaks -q aoeu");
}

void	ft_print_matrix(char **matrix)
{
	int		i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
		ft_printf("%s\n", matrix[i++]);
}

void	ft_free_pipex(t_pipex *pipex)
{
	if (!pipex)
		return ;
	ft_free_split(pipex->paths);
	free(pipex->command);
}

char *ft_prove_command(int *i, char **paths, char *cmd)
{		
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(paths[*i] ,"/");
	if (!tmp1)
		ft_error_log("JOIN_1");
	tmp2 = ft_strjoin(tmp1, cmd);
	if (!tmp1)
		ft_error_log("JOIN_2");
	free(tmp1);
	if (!access(tmp2, X_OK))
	{
		free(cmd);
		return (tmp2);
	}
	free(tmp2);
	*i += 1;
	return (NULL);
}

int	ft_exec_command(t_pipex *pipex)
{
	execv(pipex->command, pipex->arg);
	///////////////////////////////////////////////////////////////
	pipex = NULL;
	return (0);
}

char **ft_get_paths(char **env)
{
	char	**result;
	char	*str;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH", 4) && env[i])
		i++;
	result = ft_split(env[i], ':');
	if (!result)
		ft_error_log("SPLIT_ERROR");
	str = result[0];
	result[0] = ft_strdup(result[0] + 5);
	if (!result[0])
		ft_error_log("STR_DUP");
	free(str);
	return (result);
}

char	*ft_get_cmd(char *cmd)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (cmd[i] != ' ' && cmd[i])
		i++;
	str = calloc(sizeof(char), i + 1);
	if (!str)
		ft_error_log("MALLOC_CMD");
	while (j != i)
	{
		str[j] = cmd[j];
		j++;
	}
	return (str);
}

char	*ft_get_command(char **paths, char *command)
{
	char	*cmd;
	char	*tmp;
	int		i;

	i = 0;
	cmd = ft_get_cmd(command);
	if (!access(cmd, X_OK))
		return (cmd);
	while (paths[i])
	{
		tmp = ft_prove_command(&i, paths, cmd);
		if (tmp)
			return (tmp);
	}
	ft_pipex_error_log(cmd, ": command not found");
	return (NULL);
}

void	ft_first_child(t_pipex *pipex, char *infile, char *command)
{		
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		ft_pipex_error_log(infile, ": No such file or directory");
	dup2(fd, 0);
	close(pipex->pipe[0]);
	dup2(pipex->pipe[1], 1);
	pipex->command = ft_get_command(pipex->paths, command);
	pipex->arg = ft_split(command, ' ');
	ft_exec_command(pipex);
}

void	ft_second_child(t_pipex *pipex, char *outfile, char *command)
{		
	int	fd;

	fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		ft_pipex_error_log(outfile, ": Permission denied");
	dup2(fd, 1);
	close(pipex->pipe[1]);
	dup2(pipex->pipe[0], 0);
	pipex->command = ft_get_command(pipex->paths, command);
	pipex->arg = ft_split(command, ' ');
	ft_exec_command(pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex pipex;
	int		id;

	//atexit(leaks);
	if (!envp)
		ft_error_log("ME_CAGO_EN_TUS_MUERTOS");
	if (argc != 5)
		ft_error_log("USE\nUsage: ./pipex infile command1 command2 outfile");
	pipex.paths = ft_get_paths(envp);
	id = pipe(pipex.pipe);
	if (id == -1)
		ft_error_log("PIPE_OPEN");
	pipex.pid1 = fork();
	if (!pipex.pid1)
		ft_first_child(&pipex, argv[1], argv[2]);
	pipex.pid2 = fork();
	if (!pipex.pid2)
		ft_second_child(&pipex, argv[4], argv[3]);
	close(pipex.pipe[1]);
	close(pipex.pipe[0]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	//ft_free_pipex(&pipex);
	argc = 0;
	argv = NULL;
	envp = NULL;
	return (0);
}
