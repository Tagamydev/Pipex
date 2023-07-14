/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 07:23:56 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/14 07:24:57 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <pipex.h>

void	ft_first_child(t_pipex *pipex, char *infile, char *command)
{		
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		ft_pipex_error_log(infile, ": No such file or directory");
	if (dup2(fd, 0) == -1)
		ft_error_log("DUP_2_FIRST_CHILD");
	close(pipex->pipe[0]);
	if (dup2(pipex->pipe[1], 1) == -1)
		ft_error_log("DUP_2_FIRST_CHILD");
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
	if (dup2(fd, 1) == -1)
		ft_error_log("DUP_2_SECOND_CHILD");
	close(pipex->pipe[1]);
	if (dup2(pipex->pipe[0], 0) == -1)
		ft_error_log("DUP_2_SECOND_CHILD");
	pipex->command = ft_get_command(pipex->paths, command);
	pipex->arg = ft_split(command, ' ');
	ft_exec_command(pipex);
}
