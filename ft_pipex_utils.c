/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 07:25:55 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/14 07:26:16 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <pipex.h>

char	*ft_prove_command(int *i, char **paths, char *cmd)
{		
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(paths[*i], "/");
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
	int	i;

	i = execv(pipex->command, pipex->arg);
	if (i == -1)
		ft_error_log("COMMAND_EXEC");
	pipex = NULL;
	return (0);
}

char	**ft_get_paths(char **env)
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
