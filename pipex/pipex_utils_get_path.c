/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_get_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:52:43 by samusanc          #+#    #+#             */
/*   Updated: 2023/09/11 13:05:59 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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

char	*cut_input(char *input)
{
	char	*str;
	char	*result;
	size_t	i;

	i = 0;
	while (input[i] == ' ' && input[i])
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

char	*split_paths_and_compare(char *path, char *input)
{
	char	**split;
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
			break ;
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
			break ;
		i++;
	}
	if (!envp[i])
	{
		pipex->path = 0;
		return (get_address(input));
	}
	return (split_paths_and_compare(envp[i] + 5, input));
}
