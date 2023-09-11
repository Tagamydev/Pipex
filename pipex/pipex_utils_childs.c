/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_childs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:57:29 by samusanc          #+#    #+#             */
/*   Updated: 2023/09/11 13:03:24 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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

int	ft_first_child(t_pipex *pipex)
{
	char	*str;

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

int	open_last(char *str)
{
	char	*str1;
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
