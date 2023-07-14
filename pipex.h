/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:21:36 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/14 05:54:32 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# include <ft_error.h>
# include <ft_free.h>
# include <limits.h>
# include <libft.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_pipex{
	char	**paths;
	char	*command;
	char	**arg;
	int		pid1;
	int		pid2;
	int		pipe[2];
}		t_pipex;

#endif
