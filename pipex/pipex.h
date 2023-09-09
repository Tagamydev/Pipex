/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:21:36 by samusanc          #+#    #+#             */
/*   Updated: 2023/09/09 21:36:25 by samusanc         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp);

#endif
