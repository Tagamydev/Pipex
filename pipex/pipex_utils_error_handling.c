/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_error_handling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:48:55 by samusanc          #+#    #+#             */
/*   Updated: 2023/09/11 13:04:36 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	*print_cmd_not_found(char *cmd)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	errno = 127;
	return (NULL);
}

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
			ft_putstr_fd(\
			"pipex: syntax error near unexpected token `newline'\n"\
			, STDERR_FILENO);
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
